/*
** EPITECH PROJECT, 2024
** main
** File description:
** main
*/

#include "Setup.hpp"
#include "macros.hpp"
#include "IPizzaFactory.hpp"
#include <iostream>

int main(int argc, char *argv[], UNUSED char *env[])
{
    plz::Setup setup;

    try {
        setup = plz::Setup(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    std::cout << "Multiplier: " << setup.multiplier() << std::endl;
    std::cout << "Cooks: " << setup.cooks() << std::endl;
    std::cout << "Restock Time: " << setup.restock() << std::endl;

    plz::IPizzaFactory factory = plz::IPizzaFactory(setup.multiplier());
    std::vector<std::shared_ptr<plz::IPizza>> pizzas;
    std::string command;
    while (std::getline(std::cin, command)) {
        try {
            factory.tryCreateIPizzas(command, pizzas);
        } catch (const plz::IPizzaFactory::IPizzaFactoryException &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}
