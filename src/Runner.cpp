/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Runner
*/

#include "Runner.hpp"

#include <iostream>

plz::Runner::Runner(std::shared_ptr<plz::Reception> reception) : _reception(reception)
{
}

void plz::Runner::run()
{
    std::optional<std::string> command;
    fd_set readfds;
    //timeout
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    std::cout << "Hola amigo, what pizza would you like to order ?" << std::endl;
    while (this->_running) {
        FD_ZERO(&readfds);
        FD_SET(0, &readfds);

        // std::cout << "select!" << std::endl;
        select(1, &readfds, nullptr, nullptr, &tv);
        if (FD_ISSET(0, &readfds)) {
            std::cout << "FD_ISSET" << std::endl;
            command = this->getCommand();
            if (!command.has_value()) {
                std::cout << "Exiting" << std::endl;
                break;
            }
            this->handleCommand(command.value());
            std::cout << "Hola amigo, what pizza would you like to order ?" << std::endl;
        }
        this->_reception->receivePackets();
        this->_reception->handlePackets();
        this->_reception->spreadPizzas();

    }
}

std::optional<std::string> plz::Runner::getCommand()
{
    std::string command;

    std::getline(std::cin, command);
    if (std::cin.eof())
        return std::nullopt;
    if (std::cin.fail())
        throw RunnerException("Error while reading command");
    return command;
}

void plz::Runner::handleCommand(std::string command)
{
    std::function<void(std::string)> commandFunction;

    if (this->_commands.contains(command))
        commandFunction = this->_commands[command];
    else
        commandFunction = this->_commands["default"];

    try {
        commandFunction(command);
    } catch (IPizzaFactory::IPizzaFactoryException &e) {
        std::cout << e.what() << std::endl;
        return;
    }
}

plz::Runner::RunnerException::RunnerException(std::string const &message) : _message(message)
{
}

const char *plz::Runner::RunnerException::what() const noexcept
{
    return this->_message.c_str();
}
