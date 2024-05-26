/*
** EPITECH PROJECT, 2024
** Pizzas
** File description:
** APizza
*/

#pragma once

#include "IPizza.hpp"
#include "Packet.hpp"

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
            virtual const plz::Ingredients& getIngredients() const { return _ingredients; };
            virtual std::uint32_t getBakingTime() const { return _bakingTime; };

            virtual void setSize(PizzaSize size) { this->_size = size; }
            virtual void setType(PizzaType type) { this->_type = type; }
            virtual void setIngredients(plz::Ingredients& ingredients) { this->_ingredients = ingredients; }
            virtual void setBakingTime(std::uint32_t time) { this->_bakingTime = time; }

        protected:
            plz::PizzaSize _size;
            plz::PizzaType _type;
            plz::Ingredients _ingredients;
            std::uint32_t _bakingTime;
    };
}
