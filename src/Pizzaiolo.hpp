/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Pizzaiolo
*/

#pragma once

#include "IPizza.hpp"

#include <thread>
#include <memory>

namespace plz {
    class Pizzaiolo {
        public:
            Pizzaiolo();
            ~Pizzaiolo();

            void start();
            void stop();
            void queuePizza(std::shared_ptr<plz::IPizza> pizza);
            bool busy() { return _busy; }

        private:
            std::thread _thread;
            bool _busy = false;
    };
}
