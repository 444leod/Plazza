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

void plz::Kitchen::displayIngredients()
{
}

void plz::Kitchen::queuePizza(UNUSED std::shared_ptr<plz::IPizza> pizza)
{
}

std::string plz::Kitchen::_fetch()
{
    return "";
}

bool plz::Kitchen::isBusy()
{
    return false;
}

void plz::Kitchen::close()
{
}

std::pair<std::chrono::seconds, std::chrono::milliseconds> plz::Kitchen::idleTime()
{
    return {std::chrono::seconds(0), std::chrono::milliseconds(0)};
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

void plz::Kitchen::_sendBusy()
{
}

void plz::Kitchen::_sendIdle()
{
}

void plz::Kitchen::_send(UNUSED std::string message)
{
}
