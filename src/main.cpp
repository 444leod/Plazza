/*
** EPITECH PROJECT, 2024
** main
** File description:
** main
*/

#include "IPizzaFactory.hpp"
#include "macros.hpp"
#include <iostream>

int main(
    UNUSED int argc,
    UNUSED char *argv[],
    UNUSED char *env[]
)
{
    plz::IPizzaFactory factory = plz::IPizzaFactory(5);
    std::vector<std::shared_ptr<plz::IPizza>> pizzas;
    try {
        std::string command;
        std::getline(std::cin, command);
        factory.tryCreateIPizzas(command, pizzas);
    } catch (const plz::IPizzaFactory::IPizzaFactoryException &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
