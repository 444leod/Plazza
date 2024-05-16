/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#pragma once

#include "IPizza.hpp"

#include <cstdint>
#include <string>
#include <memory>
#include <vector>

namespace plz {
    class Kitchen {
        // Global
        public:
            Kitchen(uint32_t cooks, uint32_t restock);
            ~Kitchen();
            void setPid(int pid) { _pid = pid; }

            enum SIDE {
                RECEPTION,
                KITCHEN
            };
            void initPipe(Kitchen::SIDE);


        private:
            int _pid;

        // Reception side
        public:
            void displayStatus();
            void queuePizza(std::shared_ptr<plz::IPizza> pizza);

        private:
            std::string _fetch();


        // Kitchen side
        public:
            void run();

        private:
            void _readCommand();
            void _restockIngredients();
            void _cookPizzas();
            uint32_t _cooks = 0;
            uint32_t _restock = 0;
            std::vector<std::shared_ptr<plz::IPizza>> _pizzas = {};
    };
}
