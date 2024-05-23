/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Setup
*/

#include "Setup.hpp"

plz::Setup::Setup(int ac, char **av)
{
    if (ac != 4)
        throw SetupException("Bad argument count.");
    auto m = std::stod(av[1]);
    auto c = std::stoi(av[2]);
    auto r = std::stoi(av[3]);
    if (m <= 0)
        throw SetupException("Multiplier cannot be negative or zero.");
    if (c < 0)
        throw SetupException("Cannot have negative amount of pizzaiolos.");
    if (r < 0)
        throw SetupException("Restock time cannot be negative.");
    this->_multiplier = m;
    this->_pizzaiolos = c;
    this->_restock = r;
}

const plz::Setup& plz::Setup::operator=(const Setup& other)
{
    this->_multiplier = other.multiplier();
    this->_pizzaiolos = other.pizzaiolos();
    this->_restock = other.restock();
    return *this;
};
