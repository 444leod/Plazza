/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Runner
*/

#pragma once

#include "Reception.hpp"
#include "macros.hpp"

#include <memory>
#include <string>
#include <optional>
#include <map>
#include <functional>
#include <iostream>

namespace plz {
    class Runner {
        public:
            Runner() = delete;
            Runner(std::shared_ptr<plz::Reception>);
            ~Runner() = default;
            void run();
            std::optional<std::string> getCommand();
            void handleCommand(std::string command);

            class RunnerException : public std::exception {
                public:
                    RunnerException() = default;
                    RunnerException(std::string const &message);
                    ~RunnerException() = default;
                    const char *what() const noexcept override;

                private:
                    std::string _message = "Unknown error";
            };

        private:
            std::shared_ptr<plz::Reception> _reception;
            bool _running = true;


            std::map<std::string, std::function<void(std::string)>> _commands = {
                {"", [this](UNUSED std::string command) {}
                },
                {"status", [this](UNUSED std::string command) {
                    this->_reception->displayKitchenStatus();
                }},
                {"exit", [this](UNUSED std::string command) {
                    this->_running = false;
                }},
                {"default", [this](std::string command) {
                    this->_reception->handleCommand(command);
                }}
            };
    };
}
