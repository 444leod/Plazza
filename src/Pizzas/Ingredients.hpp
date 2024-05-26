/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Ingredients
*/

#pragma once

#include <cstdint>
#include <ostream>

namespace plz {
    class Ingredients {
        public:
            Ingredients() = default;
            Ingredients(uint32_t quantity);
            Ingredients(uint32_t dough, uint32_t tomato, uint32_t gruyere, uint32_t ham, uint32_t mushrooms, uint32_t steak, uint32_t eggplant, uint32_t goatCheese, uint32_t chiefLove);
            Ingredients(const Ingredients& other) = default;
            ~Ingredients();

            void addQuantity(const uint32_t quantity);
            plz::Ingredients operator+(const plz::Ingredients &other) const;
            plz::Ingredients operator-(const plz::Ingredients &other) const;
            plz::Ingredients& operator+=(const plz::Ingredients &other);
            plz::Ingredients& operator-=(const plz::Ingredients &other);
            bool operator>=(const plz::Ingredients &other) const;
            bool operator<(const plz::Ingredients &other) const;
            plz::Ingredients& operator=(const plz::Ingredients &other);

            uint32_t dough = 0;
            uint32_t tomato = 0;
            uint32_t gruyere = 0;
            uint32_t ham = 0;
            uint32_t mushrooms = 0;
            uint32_t steak = 0;
            uint32_t eggplant = 0;
            uint32_t goatCheese = 0;
            uint32_t chiefLove = 0;
        private:
    };
};

std::ostream& operator<<(std::ostream& os, const plz::Ingredients& ingredients);
