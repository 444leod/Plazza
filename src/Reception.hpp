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

#include <vector>

namespace plz {
    class Reception {
        public:
            Reception(plz::Setup& setup, plz::IPizzaFactory& factory);
            ~Reception() = default;
            void handleCommand(std::string command);
            void displayKitchenStatus();

        private:
            std::shared_ptr<plz::Kitchen> _addKitchen();
            void _spreadPizzas(std::map<std::shared_ptr<plz::Kitchen>, plz::KitchenDatas> kitchensStatus);
            bool _queuePizza(std::map<std::shared_ptr<plz::Kitchen>, plz::KitchenDatas>& kitchensStatus, std::shared_ptr<plz::IPizza> pizza);

            uint32_t _pizzaiolos;
            uint32_t _restock;
            plz::IPizzaFactory _factory;
            std::vector<std::shared_ptr<plz::Kitchen>> _kitchens = {};
            std::vector<std::shared_ptr<plz::IPizza>> _pizzas = {};
    };
}
