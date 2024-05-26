/*
** EPITECH PROJECT, 2024
** Pizzas
** File description:
** IPizza
*/

#pragma once

#include "Packet.hpp"
#include "Ingredients.hpp"
#include <cstdint>
#include <map>

namespace plz {
    enum PizzaType : uint32_t {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };

    inline std::map<PizzaType, std::string> pizzaTypeToString = {
        {Regina, "Regina"},
        {Margarita, "Margarita"},
        {Americana, "Americana"},
        {Fantasia, "Fantasia"}
    };

    enum PizzaSize : uint32_t {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };
    inline std::map<PizzaSize, std::string> pizzaSizeToString = {
        {S, "S"},
        {M, "M"},
        {L, "L"},
        {XL, "XL"},
        {XXL, "XXL"}
    };

    class IPizza {
        public:
            virtual ~IPizza() = default;
            virtual plz::PizzaSize getSize() const = 0;
            virtual plz::PizzaType getType() const = 0;
            virtual const plz::Ingredients& getIngredients() const = 0;
            virtual std::uint32_t getBakingTime() const = 0;

            virtual void setSize(PizzaSize size) = 0;
            virtual void setType(PizzaType type) = 0;
            virtual void setIngredients(plz::Ingredients& ingredients) = 0;
            virtual void setBakingTime(std::uint32_t time) = 0;

        protected:
        private:
    };
}

inline plz::Packet& operator<<(plz::Packet& packet, const plz::Ingredients& ingredients)
{
    packet << ingredients.chiefLove;
    packet << ingredients.dough;
    packet << ingredients.eggplant;
    packet << ingredients.goatCheese;
    packet << ingredients.gruyere;
    packet << ingredients.ham;
    packet << ingredients.mushrooms;
    packet << ingredients.steak;
    packet << ingredients.tomato;
    return packet;
}

inline plz::Packet& operator>>(plz::Packet& packet, plz::Ingredients& ingredients)
{
    packet >> ingredients.chiefLove;
    packet >> ingredients.dough;
    packet >> ingredients.eggplant;
    packet >> ingredients.goatCheese;
    packet >> ingredients.gruyere;
    packet >> ingredients.ham;
    packet >> ingredients.mushrooms;
    packet >> ingredients.steak;
    packet >> ingredients.tomato;
    return packet;
}

inline plz::Packet& operator<<(plz::Packet& packet, const plz::IPizza& pizza)
{
    packet << pizza.getSize();
    packet << pizza.getType();
    packet << pizza.getIngredients();
    packet << pizza.getBakingTime();
    return packet;
}

inline plz::Packet& operator>>(plz::Packet& packet, plz::IPizza& pizza)
{
    uint32_t s = pizza.getSize();
    uint32_t t = pizza.getType();
    auto i = pizza.getIngredients();
    auto b = pizza.getBakingTime();
    packet >> s >> t >> i >> b;
    pizza.setSize(static_cast<plz::PizzaSize>(s));
    pizza.setType(static_cast<plz::PizzaType>(t));
    pizza.setIngredients(i);
    pizza.setBakingTime(b);
    return packet;
}
