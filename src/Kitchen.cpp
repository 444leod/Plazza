/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include "macros.hpp"

// Global

plz::Kitchen::Kitchen(uint32_t pizzaiolos, uint32_t restock) : _pizzaiolosNumber(pizzaiolos), _restock(restock)
{
    _id = _nextId++;
    _availablePizzaiolos = pizzaiolos;
    _availableStorage = restock;
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
        std::cout << "[KITCHEN] Kitchen " << _id << " sent ready" << std::endl;
    }
}

std::optional<plz::Packet> plz::Kitchen::getPacket()
{
    plz::Packet packet;

    std::string type;
    if (_kitchenSide == plz::ProcessSide::Child)
        type = "[KITCHEN] ";
    else
        type = "[RECEPTION] ";

    if (_ipcTool->empty())
        return std::nullopt;
    std::cout << type << "Kitchen " << _id << " receiving packet (the next line is a receive and is blockant)" << std::endl;
    packet = _ipcTool->receive();
    std::cout << type << "Kitchen " << _id << " received packet! (after the blocking method)" << std::endl;
    if (packet.size() == 0)
        return std::nullopt;
    return packet;
}

void plz::Kitchen::sendPacket(plz::Packet& packet)
{
    _ipcTool->send(packet);
}



// Reception side


void plz::Kitchen::queuePizza(UNUSED std::shared_ptr<plz::IPizza> pizza)
{
    if (_availablePizzaiolos > 0) {
        _availablePizzaiolos--;
        *_ingredients -= pizza->getIngredients();
    } else if (_availableStorage > 0) {
        _availableStorage--;
    }
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
        plz::Packet packet;
        packet << "alive";
        _ipcTool->send(packet);
    }

    plz::Packet packet;
    packet << "exit";
    _ipcTool->send(packet);
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
    for (auto packet : _packetsQueue) {
        while (packet->remains() > 0) {
            std::string message;

            *packet >> message;
            if (message == "status") {
                _sendStatus();
            } else if (message == "order") {

            } else if (message == "exit") {
                _running = false;
            } else if (message == "alive") {
            } else {
                throw std::runtime_error("Invalid message received (" + message + ")");
            }
        }
    }
}

void plz::Kitchen::_sendStatus()
{
    plz::Packet packet;

    packet << "status";
    packet << _availablePizzaiolos;
    packet << _availableStorage;
    packet << _ingredients->dough;
    packet << _ingredients->tomato;
    packet << _ingredients->gruyere;
    packet << _ingredients->ham;
    packet << _ingredients->mushrooms;
    packet << _ingredients->steak;
    packet << _ingredients->eggplant;
    packet << _ingredients->goatCheese;
    packet << _ingredients->chiefLove;
    _ipcTool->send(packet);
}

void plz::Kitchen::_restockIngredients()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = now - _lastRestock;

    if (elapsed.count() > _restock) {
        *_ingredients += plz::Ingredients(1, 1, 1, 1, 1, 1, 1, 1, 1);
        _lastRestock = now;
    }
    plz::Packet packet;
    packet << "print" << "Restocked ingredients";
    _ipcTool->send(packet);
}
