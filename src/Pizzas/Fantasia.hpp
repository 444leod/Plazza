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
                    APizza(size, plz::PizzaType::Fantasia, {
                        .dough = 1,
                        .tomato = 1,
                        .gruyere = 0,
                        .ham = 0,
                        .mushrooms = 0,
                        .steak = 0,
                        .eggplant = 1,
                        .goatCheese = 1,
                        .chiefLove = 1
                    }, 4 * multiplier) {};
        };
    }
}
