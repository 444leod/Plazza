/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Cooker
*/

#pragma once

#include "IPizza.hpp"

#include <thread>
#include <memory>

namespace plz {
    class Cooker {
        public:
            Cooker();
            ~Cooker();

            void start();
            void stop();
            void queuePizza(std::shared_ptr<plz::IPizza> pizza);
            bool busy() { return _busy; }

        private:
            std::thread _thread;
            bool _busy = false;
    };
}
