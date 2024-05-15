/*
** EPITECH PROJECT, 2024
** Pizzas
** File description:
** Americana
*/

#include "APizza.hpp"

#pragma once

namespace plz {
    namespace Pizza {
        class Americana : public APizza{
            public:
                Americana(plz::PizzaSize size, double multiplier) :
                    APizza(size, plz::PizzaType::Americana, {
                        .dough = 1,
                        .tomato = 1,
                        .gruyere = 1,
                        .ham = 0,
                        .mushrooms = 0,
                        .steak = 1,
                        .eggplant = 0,
                        .goatCheese = 0,
                        .chiefLove = 0
                    }, 2 * multiplier) {};
        };
    }
}