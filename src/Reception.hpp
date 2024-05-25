/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Reception
*/

#pragma once

#include "Setup.hpp"
#include "Kitchen.hpp"
#include "IPizza.hpp"
#include "IPizzaFactory.hpp"
#include "macros.hpp"

#include <vector>

namespace plz {
    class Reception {
        public:
            Reception(plz::Setup& setup, plz::IPizzaFactory& factory);
            ~Reception();
            void handleCommand(std::string command);
            void displayKitchenStatus();
            void sendPacket(plz::Packet& packet);
            void receivePackets();
            void handlePackets();
            void spreadPizzas();

        private:
            std::shared_ptr<plz::Kitchen> _addKitchen();
            bool _queuePizza(std::shared_ptr<plz::IPizza> pizza);
            void _displayPrint(std::shared_ptr<plz::Kitchen>, std::shared_ptr<plz::Packet> packet);
            void _displayStatus(std::shared_ptr<plz::Kitchen>, std::shared_ptr<plz::Packet> packet);
            void _displayClosing(std::shared_ptr<plz::Kitchen>, UNUSED std::shared_ptr<plz::Packet> packet);
            std::optional<plz::KitchenDatas> _getKitchenStatus(std::shared_ptr<plz::Kitchen> kitchen);

            uint32_t _pizzaiolos;
            uint32_t _restock;
            plz::IPizzaFactory _factory;
            std::chrono::system_clock::time_point _lastOrder;
            std::vector<std::shared_ptr<plz::Kitchen>> _kitchens = {};
            std::vector<std::shared_ptr<plz::IPizza>> _pizzas = {};
            std::vector<std::pair<std::shared_ptr<plz::Kitchen>, std::shared_ptr<plz::Packet>>> _kitchenPackets = {};
            std::map<std::shared_ptr<plz::Kitchen>, plz::KitchenDatas> _kitchensStatus = {};
            std::map<std::string, std::function<void(std::shared_ptr<plz::Kitchen>, std::shared_ptr<plz::Packet>)>> _displayFunctions = {
                {"print",   [this](std::shared_ptr<plz::Kitchen> kitchen, std::shared_ptr<plz::Packet> packet) { this->_displayPrint(kitchen, packet); }},
                {"status",  [this](std::shared_ptr<plz::Kitchen> kitchen, std::shared_ptr<plz::Packet> packet) { this->_displayStatus(kitchen, packet); }},
                {"closing", [this](std::shared_ptr<plz::Kitchen> kitchen, std::shared_ptr<plz::Packet> packet) { this->_displayClosing(kitchen, packet); }}
            };
    };
}
