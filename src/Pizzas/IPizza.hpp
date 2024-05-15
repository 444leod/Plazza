/*
** EPITECH PROJECT, 2024
** Pizzas
** File description:
** IPizza
*/

#include <cstdint>

#pragma once

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
    
    struct Ingredrients {
        std::uint32_t dough;
        std::uint32_t tomato;
        std::uint32_t gruyere;
        std::uint32_t ham;
        std::uint32_t mushrooms;
        std::uint32_t steak;
        std::uint32_t eggplant;
        std::uint32_t goatCheese;
        std::uint32_t chiefLove;
    };

    class IPizza {
        public:
            virtual ~IPizza() = default;
            virtual plz::PizzaSize getSize() const = 0;
            virtual plz::PizzaType getType() const = 0;
            virtual const plz::Ingredrients getIngredients() const = 0;

        protected:
        private:
    };
}
