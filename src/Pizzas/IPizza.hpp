/*
** EPITECH PROJECT, 2024
** Pizzas
** File description:
** IPizza
*/


#pragma once

#include <cstdint>
#include "Ingredients.hpp"

namespace plz {
    enum PizzaType {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };

    enum PizzaSize {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    class IPizza {
        public:
            virtual ~IPizza() = default;
            virtual plz::PizzaSize getSize() const = 0;
            virtual plz::PizzaType getType() const = 0;
            virtual const plz::Ingredients getIngredients() const = 0;

        protected:
        private:
    };
}
