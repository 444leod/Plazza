/*
** EPITECH PROJECT, 2024
** Pizzas
** File description:
** APizza
*/

#include "IPizza.hpp"
#include "Ingredients.hpp"

#pragma once

namespace plz {
    class APizza: public IPizza {
        public:
            APizza(plz::PizzaSize size, plz::PizzaType type, plz::Ingredients ingredients, std::uint32_t bakingTime) :
                _size(size),
                _type(type),
                _ingredients(ingredients),
                _bakingTime(bakingTime) {};
            virtual plz::PizzaSize getSize() const { return _size; };
            virtual plz::PizzaType getType() const { return _type; };
            virtual const plz::Ingredients getIngredients() const { return _ingredients; };
            virtual std::uint32_t getBakingTime() const { return _bakingTime; };

        protected:
            const plz::PizzaSize _size;
            const plz::PizzaType _type;
            const plz::Ingredients _ingredients;
            const std::uint32_t _bakingTime;
    };
}
