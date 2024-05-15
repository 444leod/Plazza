/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** IPizzaFactory
*/

#include "IPizzaFactory.hpp"
#include "macros.hpp"
#include <iostream>

void plz::IPizzaFactory::tryCreateIPizzas(UNUSED std::string command, UNUSED std::vector<std::shared_ptr<IPizza>>& pizzas)
{
    std::string parsed;
    std::stringstream input_stringstream(command);

    while (std::getline(input_stringstream, parsed, ';'))
    {
        std::cout << parsed << std::endl;
    }
}
