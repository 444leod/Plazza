/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Ingredients
*/

#include "Ingredients.hpp"
#include <algorithm>
#include <cstdint>
#include <iostream>

plz::Ingredients::~Ingredients()
{
}

plz::Ingredients::Ingredients(uint32_t quantity) : dough(quantity), tomato(quantity), gruyere(quantity), ham(quantity), mushrooms(quantity), steak(quantity), eggplant(quantity), goatCheese(quantity), chiefLove(quantity)
{
}

plz::Ingredients::Ingredients(uint32_t dough, uint32_t tomato, uint32_t gruyere, uint32_t ham, uint32_t mushrooms, uint32_t steak, uint32_t eggplant, uint32_t goatCheese, uint32_t chiefLove) : dough(dough), tomato(tomato), gruyere(gruyere), ham(ham), mushrooms(mushrooms), steak(steak), eggplant(eggplant), goatCheese(goatCheese), chiefLove(chiefLove)
{
}


void plz::Ingredients::addQuantity(const uint32_t quantity)
{
    dough += quantity;
    tomato += quantity;
    gruyere += quantity;
    ham += quantity;
    mushrooms += quantity;
    steak += quantity;
    eggplant += quantity;
    goatCheese += quantity;
    chiefLove += quantity;
}

plz::Ingredients plz::Ingredients::operator+(const Ingredients &other) const
{
    Ingredients newIngredients;

    newIngredients.dough = dough + other.dough;
    newIngredients.tomato = tomato + other.tomato;
    newIngredients.gruyere = gruyere + other.gruyere;
    newIngredients.ham = ham + other.ham;
    newIngredients.mushrooms = mushrooms + other.mushrooms;
    newIngredients.steak = steak + other.steak;
    newIngredients.eggplant = eggplant + other.eggplant;
    newIngredients.goatCheese = goatCheese + other.goatCheese;
    newIngredients.chiefLove = chiefLove + other.chiefLove;
    return newIngredients;
}

plz::Ingredients plz::Ingredients::operator-(const Ingredients &other) const
{
    Ingredients newIngredients;

    newIngredients.dough = (other.dough < dough ? dough - other.dough : 0U);
    newIngredients.tomato = (other.tomato < tomato ? tomato - other.tomato : 0U);
    newIngredients.gruyere = (other.gruyere < gruyere ? gruyere - other.gruyere : 0U);
    newIngredients.ham = (other.ham < ham ? ham - other.ham : 0U);
    newIngredients.mushrooms = (other.mushrooms < mushrooms ? mushrooms - other.mushrooms : 0U);
    newIngredients.steak = (other.steak < steak ? steak - other.steak : 0U);
    newIngredients.eggplant = (other.eggplant < eggplant ? eggplant - other.eggplant : 0U);
    newIngredients.goatCheese = (other.goatCheese < goatCheese ? goatCheese - other.goatCheese : 0U);
    newIngredients.chiefLove = (other.chiefLove < chiefLove ? chiefLove - other.chiefLove : 0U);
    return newIngredients;
}

bool plz::Ingredients::operator>=(const Ingredients &other) const
{
    return dough >= other.dough && tomato >= other.tomato && gruyere >= other.gruyere && ham >= other.ham && mushrooms >= other.mushrooms && steak >= other.steak && eggplant >= other.eggplant && goatCheese >= other.goatCheese && chiefLove >= other.chiefLove;
}

plz::Ingredients &plz::Ingredients::operator+=(const Ingredients &other)
{
    dough += other.dough;
    tomato += other.tomato;
    gruyere += other.gruyere;
    ham += other.ham;
    mushrooms += other.mushrooms;
    steak += other.steak;
    eggplant += other.eggplant;
    goatCheese += other.goatCheese;
    chiefLove += other.chiefLove;
    return *this;
}

plz::Ingredients &plz::Ingredients::operator-=(const Ingredients &other)
{
    dough = (other.dough < dough ? dough - other.dough : 0U);
    tomato = (other.tomato < tomato ? tomato - other.tomato : 0U);
    gruyere = (other.gruyere < gruyere ? gruyere - other.gruyere : 0U);
    ham = (other.ham < ham ? ham - other.ham : 0U);
    mushrooms = (other.mushrooms < mushrooms ? mushrooms - other.mushrooms : 0U);
    steak = (other.steak < steak ? steak - other.steak : 0U);
    eggplant = (other.eggplant < eggplant ? eggplant - other.eggplant : 0U);
    goatCheese = (other.goatCheese < goatCheese ? goatCheese - other.goatCheese : 0U);
    chiefLove = (other.chiefLove < chiefLove ? chiefLove - other.chiefLove : 0U);
    return *this;
}

plz::Ingredients &plz::Ingredients::operator=(const Ingredients &other)
{
    dough = other.dough;
    tomato = other.tomato;
    gruyere = other.gruyere;
    ham = other.ham;
    mushrooms = other.mushrooms;
    steak = other.steak;
    eggplant = other.eggplant;
    goatCheese = other.goatCheese;
    chiefLove = other.chiefLove;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const plz::Ingredients &ingredients)
{
    os << "Dough: " << ingredients.dough << std::endl;
    os << "Tomato: " << ingredients.tomato << std::endl;
    os << "Gruyere: " << ingredients.gruyere << std::endl;
    os << "Ham: " << ingredients.ham << std::endl;
    os << "Mushrooms: " << ingredients.mushrooms << std::endl;
    os << "Steak: " << ingredients.steak << std::endl;
    os << "Eggplant: " << ingredients.eggplant << std::endl;
    os << "Goat cheese: " << ingredients.goatCheese << std::endl;
    os << "Chief love: " << ingredients.chiefLove << std::endl;
    return os;
}
