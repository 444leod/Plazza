/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include "macros.hpp"
#include "Regina.hpp"

// Global

plz::Kitchen::Kitchen(uint32_t pizzaiolos, uint32_t restockTime) : _pizzaiolosNumber(pizzaiolos), _restockTime(restockTime)
{
    _id = _nextId++;
    _availablePizzaiolos = pizzaiolos;
    _availableStorage = pizzaiolos;
}

plz::Kitchen::~Kitchen()
{
}

void plz::Kitchen::initPipe(plz::ProcessSide side)
{
    _kitchenSide = side;
    _ipcTool = std::make_shared<plz::IpcTool>(std::to_string(_fork->getChildPid()), side);
    if (side == plz::ProcessSide::Child) {
        //wait for 100 milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        plz::Packet packet;
        packet << "ready";
        _ipcTool->send(packet);
        _lastActivity = std::chrono::system_clock::now();
        _threadPool = std::make_shared<ThreadPool>(_pizzaiolosNumber);
        _threadPool->start();
    }
}

std::optional<plz::Packet> plz::Kitchen::getPacket()
{
    plz::Packet packet;

    if (_ipcTool->empty())
        return std::nullopt;
    packet = _ipcTool->receive();
    if (packet.fail())
        throw std::runtime_error("Invalid packet received");
    if (packet.size() == 0)
        return std::nullopt;
    return packet;
}

void plz::Kitchen::sendPacket(plz::Packet& packet)
{
    _ipcTool->send(packet);
}



// Reception side


void plz::Kitchen::queuePizza(std::shared_ptr<plz::IPizza> pizza)
{
    plz::Packet packet;

    packet << "order";
    packet << *pizza;
    _ipcTool->send(packet);
}

std::string plz::Kitchen::_fetch()
{
    return "";
}

void plz::Kitchen::close()
{
    plz::Packet packet;
    packet << "exit";
    _ipcTool->send(packet);
    _running = false;
    _fork->waitFork();
}

void plz::Kitchen::waitFork()
{
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();

    while (!this->_readForkInit()) {
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        if (elapsed_seconds.count() > 1)
            throw std::runtime_error("Fork timeout");
    }
}

bool plz::Kitchen::_readForkInit()
{
    std::shared_ptr<plz::Packet> packet;
    std::string message;

    if (_ipcTool->empty())
        return false;

    packet = std::make_shared<plz::Packet>(_ipcTool->receive());
    if (packet->fail())
        throw std::runtime_error("Invalid packet received");
    if (packet->size() == 0)
        return false;
    *packet >> message;

    if (packet->fail())
        throw std::runtime_error("Invalid packet received");
    if (message != "ready")
        throw std::runtime_error("Invalid message received (" + message + ")");

    if (packet->remains() > 0)
        _packetsQueue.push_back(packet);
    return true;
}

std::vector<std::shared_ptr<plz::Packet>>& plz::Kitchen::getWaitingPackets()
{
    return _packetsQueue;
}


// Kitchen side

void plz::Kitchen::run()
{
    _lastRestock = std::chrono::system_clock::now();
    while (_running) {
        _queueReceivedPacket();
        _restockIngredients();
        _handlePackets();
        _spreadPizzas();
        _verifyClosing();
    }

    plz::Packet packet;
    packet << "exit";
    _ipcTool->send(packet);
}

void plz::Kitchen::_spreadPizzas()
{
    if (_pizzas.size() == 0)
        return;
    if (_threadPool->occupiedThreads() >= _pizzaiolosNumber)
        return;
    auto pizza = _pizzas.front();
    auto pizzaIngredients = pizza->getIngredients();

    if ((*_ingredients) < pizzaIngredients)
        return;
    *_ingredients = (*_ingredients) - pizzaIngredients;
    _pizzas.erase(_pizzas.begin());
    _threadPool->queueJob([this, pizza]() {
        std::chrono::seconds time = std::chrono::seconds(pizza->getBakingTime());
        std::this_thread::sleep_for(time);

        plz::Packet packet;
        packet << "print";
        std::string str = "a " + pizzaSizeToString[pizza->getSize()] + " " + pizzaTypeToString[pizza->getType()] + " is ready!";
        packet << str;
        _printMutex.lock();
        _ipcTool->send(packet);
        _printMutex.unlock();

        _activityMutex.lock();
        _lastActivity = std::chrono::system_clock::now();
        _activityMutex.unlock();
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void plz::Kitchen::_queueReceivedPacket()
{
    std::optional<plz::Packet> packet = this->getPacket();

    if (!packet.has_value())
        return;
    _packetsQueue.push_back(std::make_shared<plz::Packet>(packet.value()));
}

void plz::Kitchen::_handlePackets()
{
    if (_packetsQueue.size() == 0)
        return;
    auto packet = _packetsQueue.front();
    _packetsQueue.erase(_packetsQueue.begin());
    std::string message;
    *packet >> message;
    if (message == "displayStatus") {
        _sendDisplayStatus();
    } else if (message == "status") {
        _sendStatus();
    } else if (message == "order") {
        if (_pizzas.size() > _pizzaiolosNumber)
            throw std::runtime_error("Too many pizzas in queue");
        plz::APizza pizza(S, plz::PizzaType::Americana, plz::Ingredients(), 2);
        *packet >> pizza;
        _pizzas.push_back(std::make_shared<plz::APizza>(pizza));
    } else if (message == "exit") {
        _running = false;
    } else {
        throw std::runtime_error("Invalid message received (" + message + ")");
    }
    if (packet->remains() > 0)
        _packetsQueue.push_back(packet);
}

void plz::Kitchen::_sendStatus()
{
    plz::Packet packet;

    uint32_t storage = _pizzas.size();

    packet << "status";
    packet << _threadPool->occupiedThreads();
    packet << storage;
    packet << *_ingredients;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    _ipcTool->send(packet);
}

void plz::Kitchen::_sendDisplayStatus()
{
    plz::Packet packet;

    uint32_t storage = _pizzas.size();

    packet << "displayStatus";
    packet << _threadPool->occupiedThreads();
    packet << storage;
    packet << *_ingredients;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    _ipcTool->send(packet);
}

void plz::Kitchen::_restockIngredients()
{
    auto now = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastRestock).count();

    if (elapsed > _restockTime) {
        *_ingredients += plz::Ingredients(1, 1, 1, 1, 1, 1, 1, 1, 1);
        _lastRestock = now;
    }
}

void plz::Kitchen::_verifyClosing()
{
    if (_threadPool->occupiedThreads() != 0)
        return;
    auto now = std::chrono::system_clock::now();
    _activityMutex.lock();
    auto lastActivity = _lastActivity;
    _activityMutex.unlock();

    if (now - lastActivity > std::chrono::milliseconds(5000)) {
        _running = false;
    }
}
