/*
** EPITECH PROJECT, 2024
** main
** File description:
** main
*/

#include "IPizzaFactory.hpp"
#include "macros.hpp"

int main(
    UNUSED int argc,
    UNUSED char *argv[],
    UNUSED char *env[]
)
{
    plz::IPizzaFactory factory;
    std::vector<std::shared_ptr<plz::IPizza>> pizzas;
    factory.tryCreateIPizzas("margarita XL x2;margarita XL x2;margarita XL x2;margarita XL x2;", pizzas);
    return 0;
}
