/*
** EPITECH PROJECT, 2024
** main
** File description:
** main
*/

#include "Setup.hpp"
#include "macros.hpp"
#include "NamedPipes.hpp"
#include "IPizzaFactory.hpp"
#include "Runner.hpp"
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

    // std::cout << "Multiplier: " << setup.multiplier() << std::endl;
    // std::cout << "Pizzaiolos: " << setup.pizzaiolos() << std::endl;
    // std::cout << "Restock Time: " << setup.restock() << std::endl;

    plz::IPizzaFactory factory = plz::IPizzaFactory(setup.multiplier());

    std::shared_ptr<plz::Reception> reception = std::make_shared<plz::Reception>(setup, factory);
    plz::Runner runner = plz::Runner(reception);

    try {
        runner.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
