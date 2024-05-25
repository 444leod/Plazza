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
                    APizza(size, plz::PizzaType::Margarita, {
                        .dough = 1,
                        .tomato = 1,
                        .gruyere = 1,
                        .ham = 0,
                        .mushrooms = 0,
                        .steak = 0,
                        .eggplant = 0,
                        .goatCheese = 0,
                        .chiefLove = 0
                    }, 1 * multiplier) {};
        };
    }
}
