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
            virtual plz::PizzaSize getSize() = 0;
            virtual plz::PizzaType getType() = 0;

        protected:
            plz::PizzaSize _size;
            plz::PizzaType _type;
            
    };
}
