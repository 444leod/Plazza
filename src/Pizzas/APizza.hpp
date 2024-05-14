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
            virtual plz::PizzaSize getSize() { return _size; };
            virtual plz::PizzaType getType() { return _type; };

        protected:
            plz::PizzaSize _size;
            plz::PizzaType _type;

    };
}
