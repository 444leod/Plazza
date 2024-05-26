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
    std::shared_ptr<lib::FileDescriptorMonitor> monitor = std::make_shared<lib::FileDescriptorMonitor>();
    monitor->addReadFd(0);
    monitor->setTimeout(std::chrono::seconds(0), std::chrono::milliseconds(0));

    while (this->_running) {
        monitor->watch();
        if (monitor->isReadable(0) == false)
            continue;
        command = this->getCommand();
        if (!command.has_value()) {
            std::cout << "Exiting" << std::endl;
            break;
        }
        this->handleCommand(command.value());
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
