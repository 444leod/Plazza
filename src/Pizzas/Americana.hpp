/*
** EPITECH PROJECT, 2024
** Pizzas
** File description:
** Americana
*/


#pragma once

#include "APizza.hpp"

namespace plz {
    namespace Pizza {
        class Americana : public APizza{
            public:
                Americana(plz::PizzaSize size, double multiplier) :
                    APizza(size, plz::PizzaType::Americana, plz::Ingredients(1, 1, 1, 0, 0, 1, 0, 0, 0), 2 * multiplier) {};
        };
    }
}


