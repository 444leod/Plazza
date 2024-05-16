/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#pragma once

#include "IPizza.hpp"
#include "Cooker.hpp"

#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <chrono>

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
            void displayIngredients();
            void queuePizza(std::shared_ptr<plz::IPizza> pizza);
            bool isBusy();
            void close();
            std::pair<std::chrono::seconds, std::chrono::milliseconds> idleTime();

        private:
            std::string _fetch();


        // Kitchen side
        public:
            void run();

        private:
            void _readCommand();
            void _restockIngredients();
            void _cookPizzas();
            void _sendBusy();
            void _sendIdle();
            void _send(std::string message);

            uint32_t _cooks = 0;
            uint32_t _restock = 0;
            std::vector<std::shared_ptr<plz::IPizza>> _pizzas = {};
            std::shared_ptr<plz::Ingredrients> _ingredients = std::make_shared<plz::Ingredrients>(5, 5, 5, 5, 5, 5, 5, 5 ,5);
            std::chrono::time_point<std::chrono::system_clock> _lastActivity;
            std::vector<std::shared_ptr<plz::Cooker>> _cookers = {};
    };
}
