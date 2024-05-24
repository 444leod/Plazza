/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** IPizzaFactory
*/

#include "IPizzaFactory.hpp"

void plz::IPizzaFactory::tryCreateIPizzas(std::string command, std::vector<std::shared_ptr<IPizza>>& pizzas)
{
    std::string parsed;
    std::stringstream input_stringstream(command);
    std::vector<std::shared_ptr<IPizza>> tmpPizzas;

    while (std::getline(input_stringstream, parsed, ';'))
    {
        std::string pizzaType, pizzaSize, nbPizzas, errorVerif;
        std::istringstream iss(parsed);
        int nbPizzasInt;
        iss >> pizzaType >> pizzaSize >> nbPizzas;
        if (iss.fail() || iss >> errorVerif)
            throw IPizzaFactoryException("Invalid pizza command!");
        if (_pizzaTypeMap.find(pizzaType) == _pizzaTypeMap.end())
            throw IPizzaFactoryException("Invalid pizza type!");
        if (_pizzaSizeMap.find(pizzaSize) == _pizzaSizeMap.end())
            throw IPizzaFactoryException("Invalid pizza size!");
        if (nbPizzas[0] != 'x')
            throw IPizzaFactoryException("Invalid prefix for number of pizzas!");
        try {
            nbPizzasInt = std::stoi(nbPizzas.erase(0, 1));
        } catch (std::exception &e) {
            throw IPizzaFactoryException("Invalid number of pizzas!");
        }
        if (nbPizzasInt <= 0 || nbPizzasInt > 99)
            throw IPizzaFactoryException("Invalid number of pizzas, must be between 1 and 99!");
        for (int i = 0; i < nbPizzasInt; i++)
            tmpPizzas.push_back(_pizzaFactory[_pizzaTypeMap[pizzaType]](_pizzaSizeMap[pizzaSize], _multiplier));
    }
    pizzas = tmpPizzas;
}
