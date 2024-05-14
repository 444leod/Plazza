/*
** EPITECH PROJECT, 2024
** Pizzas
** File description:
** APizza
*/

#include "IPizza.hpp"

#pragma once

namespace plz {
    class APizza: public IPizza {
        public:
            APizza() = default;
            ~APizza() = default;
            virtual plz::PizzaSize getSize() const { return _size; };
            virtual plz::PizzaType getType() const { return _type; };
            virtual const plz::Ingredrients getIngredients() const { return _ingredients; };

        protected:
            const plz::PizzaSize _size;
            const plz::PizzaType _type;
            const plz::Ingredrients _ingredients;
    };
}
