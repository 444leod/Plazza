/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include "macros.hpp"

// Global

plz::Kitchen::Kitchen(uint32_t pizzaiolos, uint32_t restock) : _pizzaiolosNumber(pizzaiolos), _restock(restock)
{
    _id = _nextId++;
    _availablePizzaiolos = pizzaiolos;
    _availableStorage = restock;
}

plz::Kitchen::~Kitchen()
{
}

void plz::Kitchen::initPipe(UNUSED SIDE side)
{
}


// Reception side

const plz::Ingredients plz::Kitchen::getIngredients()
{
    return *_ingredients;
}

void plz::Kitchen::queuePizza(UNUSED std::shared_ptr<plz::IPizza> pizza)
{
    if (_availablePizzaiolos > 0) {
        _availablePizzaiolos--;
        *_ingredients -= pizza->getIngredients();
    } else if (_availableStorage > 0) {
        _availableStorage--;
    }
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

uint32_t plz::Kitchen::nbOfAvailablePizzaiolos()
{
    return _availablePizzaiolos;
}

uint32_t plz::Kitchen::nbOfAvailableStorage()
{
    return _availableStorage;
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

void plz::Kitchen::_pizzaioloPizzas()
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
