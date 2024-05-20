/*
** EPITECH PROJECT, 2024
** Pizzas
** File description:
** Regina
*/

#include "APizza.hpp"

#pragma once

namespace plz {
    namespace Pizza {
        class Regina : public APizza{
            public:
                Regina(plz::PizzaSize size, double multiplier) :
                    APizza(size, plz::PizzaType::Regina, plz::Ingredients(1, 1, 1, 1, 1, 0, 0, 0, 0), 2 * multiplier) {};
        };
    }
}


