/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Runner
*/

#include "Runner.hpp"
#include "FileDescriptorMonitor.hpp"

#include <iostream>

plz::Runner::Runner(std::shared_ptr<plz::Reception> reception) : _reception(reception)
{
}

void plz::Runner::run()
{
    std::optional<std::string> command;
    lib::FileDescriptorMonitor monitor;

    std::cout << "Ciao amigo, what pizza would you like to order ?" << std::endl;
    while (this->_running) {
        std::vector<int> readFds = {0};
        std::vector<int> writeFds = {};
        monitor.monitor(readFds, writeFds);
        if (readFds.size() > 0) {
            command = this->getCommand();
            if (!command.has_value()) {
                std::cout << "Exiting" << std::endl;
                break;
            }
            this->handleCommand(command.value());
            std::cout << "Ciao amigo, what pizza would you like to order ?" << std::endl;
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
