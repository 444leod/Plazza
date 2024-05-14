/*
** EPITECH PROJECT, 2024
** Pizzas
** File description:
** Americana
*/

#include "APizza.hpp"

#pragma once

namespace plz {
    class Americana : public APizza{
        public:
            Americana(plz::PizzaSize size, double multiplier) :
                _size(size),
                _type(plz::PizzaType::Americana),
                _ingredients({
                    .dough = 1,
                    .tomato = 1,
                    .gruyere = 1,
                    .ham = 0,
                    .mushrooms = 0,
                    .steak = 1,
                    .eggplant = 0,
                    .goatCheese = 0,
                    .chiefLove = 0
                }),
                _bakingTime(2 * multiplier) {};
            ~Americana();

        private:
            const plz::PizzaSize _size;
            const plz::PizzaType _type;
            const plz::Ingredrients _ingredients;
            const std::uint32_t _bakingTime;
    };
}
