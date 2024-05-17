/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Reception
*/

#include "Reception.hpp"
#include "IPizzaFactory.hpp"
#include "macros.hpp"

plz::Reception::Reception(plz::Setup setup, plz::IPizzaFactory factory) : _pizzaiolos(setup.pizzaiolos()), _restock(setup.restock()), _factory(factory)
{
}

void plz::Reception::handleCommand(UNUSED std::string command)
{
}

void plz::Reception::displayKitchenStatus()
{
}

void plz::Reception::_addKitchen()
{
}
