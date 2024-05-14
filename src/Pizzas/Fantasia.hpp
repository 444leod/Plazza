/*
** EPITECH PROJECT, 2024
** Pizzas
** File description:
** Fantasia
*/

#include "APizza.hpp"

#pragma once

namespace plz {
    class Fantasia : public APizza{
        public:
            Fantasia(plz::PizzaSize size, double multiplier) :
                _size(size),
                _type(plz::PizzaType::Fantasia),
                _ingredients({
                    .dough = 1,
                    .tomato = 1,
                    .gruyere = 0,
                    .ham = 0,
                    .mushrooms = 0,
                    .steak = 0,
                    .eggplant = 1,
                    .goatCheese = 1,
                    .chiefLove = 1
                }),
                _bakingTime(4 * multiplier) {};
            ~Fantasia();

        private:
            const plz::PizzaSize _size;
            const plz::PizzaType _type;
            const plz::Ingredrients _ingredients;
            const std::uint32_t _bakingTime;
    };
}
