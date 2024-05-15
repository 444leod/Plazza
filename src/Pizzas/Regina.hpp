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
                    APizza(size, plz::PizzaType::Regina, {
                        .dough = 1,
                        .tomato = 1,
                        .gruyere = 1,
                        .ham = 1,
                        .mushrooms = 1,
                        .steak = 0,
                        .eggplant = 0,
                        .goatCheese = 0,
                        .chiefLove = 0
                    }, 2 * multiplier) {};
        };
    }
}
