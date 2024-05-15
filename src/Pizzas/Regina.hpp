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
                    _size(size),
                    _type(plz::PizzaType::Regina),
                    _ingredients({
                        .dough = 1,
                        .tomato = 1,
                        .gruyere = 1,
                        .ham = 1,
                        .mushrooms = 1,
                        .steak = 0,
                        .eggplant = 0,
                        .goatCheese = 0,
                        .chiefLove = 0
                    }),
                    _bakingTime(2 * multiplier) {};
                ~Regina();

            private:
                const plz::PizzaSize _size;
                const plz::PizzaType _type;
                const plz::Ingredrients _ingredients;
                const std::uint32_t _bakingTime;
        };
    }
}
