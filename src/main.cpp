/*
** EPITECH PROJECT, 2024
** main
** File description:
** main
*/

#include "Setup.hpp"
#include "macros.hpp"
#include <iostream>

int main(int argc, char *argv[], UNUSED char *env[])
{
    plz::Setup setup;

    try {
        setup = plz::Setup(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    std::cout << "Multiplier: " << setup.multiplier() << std::endl;
    std::cout << "Cooks: " << setup.cooks() << std::endl;
    std::cout << "Restock Time: " << setup.restock() << std::endl;
    return 0;
}
