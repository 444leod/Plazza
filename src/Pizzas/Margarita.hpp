/*
** EPITECH PROJECT, 2024
** Pizzas
** File description:
** Margarita
*/

#include "APizza.hpp"

#pragma once

namespace plz {
    class Margarita : public APizza{
        public:
            Margarita(plz::PizzaSize size) :
                _size(size),
                _type(plz::PizzaType::Margarita),
                _ingredients({
                    .dough = 1,
                    .tomato = 1,
                    .gruyere = 1,
                    .ham = 0,
                    .mushrooms = 0,
                    .steak = 0,
                    .eggplant = 0,
                    .goatCheese = 0,
                    .chiefLove = 0
                }),
                _bakingTime(1) {};
            ~Margarita();

        private:
            const plz::PizzaSize _size;
            const plz::PizzaType _type;
            const plz::Ingredrients _ingredients;
            const std::uint32_t _bakingTime;
    };
}
