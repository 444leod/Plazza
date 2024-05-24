/*
** EPITECH PROJECT, 2024
** Pizzas
** File description:
** Margarita
*/

#pragma once

#include "APizza.hpp"

namespace plz {
    namespace Pizza {
        class Margarita : public APizza{
            public:
                Margarita(plz::PizzaSize size, double multiplier) :
                    APizza(size, plz::PizzaType::Margarita, plz::Ingredients(1, 1, 1, 0, 0, 0, 0, 0, 0), 1 * multiplier) {};
        };
    }
}
