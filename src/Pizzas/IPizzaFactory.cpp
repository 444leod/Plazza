/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** IPizzaFactory
*/

#include "IPizzaFactory.hpp"
#include "macros.hpp"
#include <iostream>

void plz::IPizzaFactory::tryCreateIPizzas(std::string command, UNUSED std::vector<std::shared_ptr<IPizza>>& pizzas)
{
    std::string parsed;
    std::stringstream input_stringstream(command);

    while (std::getline(input_stringstream, parsed, ';'))
    {
        std::string pizzaType, pizzaSize, nbPizzas, errorVerif;
        std::istringstream iss(parsed);
        iss >> pizzaType >> pizzaSize >> nbPizzas;
        if (iss.fail() || iss >> errorVerif)
            throw IPizzaFactoryException("Invalid pizza command!");
    }
}
