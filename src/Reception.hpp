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

#include <vector>

namespace plz {
    class Reception {
        public:
            Reception();
            ~Reception() = default;
            void handleCommand(std::string command);
            void displayKitchenStatus();

        private:
            void _addKitchen();

            std::vector<plz::Kitchen> _kitchens;
            std::vector<std::shared_ptr<plz::IPizza>> _pizzas;
    };
}
