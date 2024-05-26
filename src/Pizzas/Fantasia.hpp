/*
** EPITECH PROJECT, 2024
** Pizzas
** File description:
** Fantasia
*/

#pragma once

#include "APizza.hpp"

namespace plz {
    namespace Pizza {
        class Fantasia : public APizza{
            public:
                Fantasia(plz::PizzaSize size, double multiplier) :
                    APizza(size, plz::PizzaType::Fantasia, plz::Ingredients(1, 1, 0, 0, 0, 0, 1, 1, 1), 4 * multiplier) {};
        };
    }
}


