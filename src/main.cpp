/*
** EPITECH PROJECT, 2024
** main
** File description:
** main
*/

#include "macros.hpp"
#include <cstdint>
#include <iostream>

int main(
    UNUSED int argc,
    char *argv[],
    UNUSED char *env[]
)
{
    double multiplier;
    std::uint32_t nbCooks;
    std::uint32_t restockTime;

    try {
        multiplier = std::stod(argv[1]);
        nbCooks = std::stoi(argv[2]);
        restockTime = std::stoi(argv[3]);
    } catch (std::exception &e) {
        return 84;
    }
    if (nbCooks <= 0)
        return 84;

    (void) multiplier;
    (void) restockTime;
    return 0;
}
