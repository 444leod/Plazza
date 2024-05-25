/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Reception
*/

#include "Reception.hpp"
#include "IPizzaFactory.hpp"
#include "macros.hpp"
#include "Fork.hpp"

#include <iostream>

plz::Reception::Reception(plz::Setup& setup, plz::IPizzaFactory& factory) : _pizzaiolos(setup.pizzaiolos()), _restock(setup.restock()), _factory(factory)
{
}

plz::Reception::~Reception()
{
    for (auto& kitchen : _kitchens) {
        kitchen->close();
    }
}

bool plz::Reception::_queuePizza(std::shared_ptr<plz::IPizza> pizza)
{
    std::vector<std::shared_ptr<plz::Kitchen>> kitchenByIdleTime;
    for (auto& kitchen : _kitchens) {
        if (_kitchensStatus[kitchen].idleTime.count() > 0) {
            kitchenByIdleTime.push_back(kitchen);
        }
    }
    std::sort(kitchenByIdleTime.begin(), kitchenByIdleTime.end(), [&](std::shared_ptr<plz::Kitchen> a, std::shared_ptr<plz::Kitchen> b) {
        return _kitchensStatus[a].idleTime < _kitchensStatus[b].idleTime;
    });

    for (auto& kitchen : kitchenByIdleTime) {
        if (_kitchensStatus[kitchen].pizzaiolos == kitchen->pizzaiolos() && _kitchensStatus[kitchen].restock == kitchen->restock() && _kitchensStatus[kitchen].ingredients >= pizza->getIngredients()) {
            kitchen->queuePizza(pizza);

            _kitchensStatus[kitchen].pizzaiolos--;
            _kitchensStatus[kitchen].restock--;
            _kitchensStatus[kitchen].ingredients -= pizza->getIngredients();
            return true;
        }
    }
    for (auto& kitchen : _kitchens) {
        if (_kitchensStatus[kitchen].pizzaiolos > 0 && _kitchensStatus[kitchen].ingredients >= pizza->getIngredients()) {
            kitchen->queuePizza(pizza);

            _kitchensStatus[kitchen].pizzaiolos--;
            _kitchensStatus[kitchen].ingredients -= pizza->getIngredients();
            return true;
        }
    }
    for (auto& kitchen : _kitchens) {
        if (_kitchensStatus[kitchen].restock > 0 && _kitchensStatus[kitchen].ingredients >= pizza->getIngredients()) {
            kitchen->queuePizza(pizza);

            _kitchensStatus[kitchen].restock--;
            _kitchensStatus[kitchen].ingredients -= pizza->getIngredients();
            return true;
        }
    }
    return false;
}

void plz::Reception::spreadPizzas()
{
    std::shared_ptr<plz::Kitchen> kitchen;

    if (_pizzas.empty())
        return;
    if (_kitchensStatus.size() != _kitchens.size()) {
        auto now = std::chrono::system_clock::now();
        if (now - _lastOrder < std::chrono::milliseconds(500)) {
            std::cout << "[RECEPTION] Kitchens are taking too long to respond..." << std::endl;
            _lastOrder = now;
        }
        return;
    }

    std::cout << "[RECEPTION] Spreading pizzas..." << std::endl;
    for (auto& pizza : _pizzas) {
        if (!_queuePizza(pizza)) {
            kitchen = _addKitchen();
            kitchen->queuePizza(pizza);
            plz::KitchenDatas kitchenStatus = {
                kitchen->pizzaiolos() - 1,
                kitchen->restock(),
                plz::Ingredients(5) - pizza->getIngredients(),
                std::chrono::milliseconds(0)
            };
            _kitchensStatus[kitchen] = kitchenStatus;
        }
    }
    std::cout << "[RECEPTION] Pizzas spread!" << std::endl;
    _pizzas.clear();
    _kitchensStatus.clear();
}

void plz::Reception::handleCommand(UNUSED std::string command)
{
    _factory.tryCreateIPizzas(command, _pizzas);
}

std::shared_ptr<plz::Kitchen> plz::Reception::_addKitchen()
{
    std::shared_ptr<plz::Kitchen> kitchen = std::make_shared<plz::Kitchen>(_pizzaiolos, _restock);

    _kitchens.push_back(kitchen);
    std::shared_ptr<plz::Fork> fork = std::make_shared<plz::Fork>();
    kitchen->setFork(fork);

    if (fork->isChild()) {
        kitchen->setPid(fork->getParentPid());
        kitchen->initPipe(plz::ProcessSide::Child);
        try {
            kitchen->run();
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            plz::Packet packet;
            packet << "error";
            kitchen->sendPacket(packet);
            std::exit(84);
        }
        std::exit(0);
    }
    kitchen->setPid(fork->getChildPid());
    kitchen->initPipe(plz::ProcessSide::Parent);
    std::cout << "[RECEPTION] Waiting for kitchen " << kitchen->id() << " to be ready..." << std::endl;
    kitchen->waitFork();
    std::vector<std::shared_ptr<plz::Packet>> packets = kitchen->getWaitingPackets();
    for (auto &packet : packets) {
        _kitchenPackets.push_back(std::make_pair(
            kitchen,
            packet
        ));
    }
    std::cout << "[RECEPTION] Kitchen " << kitchen->id() << " is ready!" << std::endl;
    return kitchen;
}

void plz::Reception::receivePackets()
{
    std::optional<plz::Packet> packet;

    for (auto &kitchen : _kitchens) {
        packet = kitchen->getPacket();
        if (packet.has_value()) {
            std::cout << "[RECEPTION] Received packet from kitchen " << kitchen->id() << std::endl;
            _kitchenPackets.push_back(std::make_pair(
                kitchen,
                std::make_shared<plz::Packet>(packet.value())
            ));
        }
    }
}

void plz::Reception::handlePackets()
{
    std::string packetStr;

    for (auto &kitchenPacket : _kitchenPackets) {
        (*kitchenPacket.second) >> packetStr;
        if (_displayFunctions.contains(packetStr)) {
            _displayFunctions[packetStr](kitchenPacket.first, kitchenPacket.second);
        } else {
            throw std::runtime_error("Unknown packet type (" + packetStr + ")");
        }
    }
    _kitchenPackets.clear();
}

void plz::Reception::sendPacket(plz::Packet& packet)
{
    for (auto &kitchen : _kitchens) {
        kitchen->sendPacket(packet);
    }
}

void plz::Reception::_displayStatus(std::shared_ptr<plz::Kitchen> kitchen, std::shared_ptr<plz::Packet> packet)
{
    plz::KitchenDatas datas;
    (*packet) >> datas.pizzaiolos;
    (*packet) >> datas.restock;
    (*packet) >> datas.ingredients.dough;
    (*packet) >> datas.ingredients.tomato;
    (*packet) >> datas.ingredients.gruyere;
    (*packet) >> datas.ingredients.ham;
    (*packet) >> datas.ingredients.mushrooms;
    (*packet) >> datas.ingredients.steak;
    (*packet) >> datas.ingredients.eggplant;
    (*packet) >> datas.ingredients.goatCheese;
    (*packet) >> datas.ingredients.chiefLove;

    _kitchensStatus[kitchen] = datas;
    plz::Ingredients ingredients = datas.ingredients;

    std::printf("┌───────────────────────────────────┐\n");
    std::printf("│                                   │\n");
    std::printf("│            Pizzeria %.3d           │\n", kitchen->id());
    std::printf("│                                   │\n");
    std::printf("│      Cooking pizzas: %3d/%-3d      │\n", datas.pizzaiolos - kitchen->pizzaiolos(), datas.restock);
    std::printf("│     Storaged pizzas: %3d/%-3d      │\n", datas.restock - kitchen->restock(), datas.restock);
    std::printf("│                                   │\n");
    std::printf("│           Ingredients:            │\n");
    std::printf("│                                   │\n");
    std::printf("│ %3d dough         %3d tomato      │\n", ingredients.dough, ingredients.tomato);
    std::printf("│ %3d gruyere       %3d ham         │\n", ingredients.gruyere, ingredients.ham);
    std::printf("│ %3d mushrooms     %3d steak       │\n", ingredients.mushrooms, ingredients.steak);
    std::printf("│ %3d eggplant      %3d goatCheese  │\n", ingredients.eggplant, ingredients.goatCheese);
    std::printf("│ %3d chiefLove                     │\n", ingredients.chiefLove);
    std::printf("│                                   │\n");
    std::printf("└───────────────────────────────────┘\n");
}

void plz::Reception::_displayPrint(std::shared_ptr<plz::Kitchen> kitchen, std::shared_ptr<plz::Packet> packet)
{
    std::string print;

    (*packet) >> print;
    std::printf("Kitchen %3d: ", kitchen->id());
    std::cout << print << std::endl;
}

void plz::Reception::_displayClosing(std::shared_ptr<plz::Kitchen> kitchen, UNUSED std::shared_ptr<plz::Packet> packet)
{
    std::printf("Kitchen %d is closing\n", kitchen->id());
    if (_kitchensStatus.contains(kitchen))
        _kitchensStatus.erase(kitchen);
    _kitchens.erase(std::remove(_kitchens.begin(), _kitchens.end(), kitchen), _kitchens.end());
}
