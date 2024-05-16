/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include "macros.hpp"

// Global

plz::Kitchen::Kitchen(uint32_t cooks, uint32_t restock) : _cooks(cooks), _restock(restock)
{
}

plz::Kitchen::~Kitchen()
{
}

void plz::Kitchen::initPipe(UNUSED SIDE side)
{
}


// Reception side

void plz::Kitchen::displayStatus()
{
}

void plz::Kitchen::queuePizza(UNUSED std::shared_ptr<plz::IPizza> pizza)
{
}

std::string plz::Kitchen::_fetch()
{
    return "";
}


// Kitchen side

void plz::Kitchen::run()
{
}

void plz::Kitchen::_readCommand()
{
}

void plz::Kitchen::_restockIngredients()
{
}

void plz::Kitchen::_cookPizzas()
{
}


