/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** APizzaFactory
*/

#pragma once

#include "IPizza.hpp"
#include "Margarita.hpp"
#include "Regina.hpp"
#include "Americana.hpp"
#include "Fantasia.hpp"
#include "macros.hpp"

#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <functional>
#include <sstream>


namespace plz {
    class IPizzaFactory {
        public:
            IPizzaFactory(double multiplier) : _multiplier(multiplier) {};
            ~IPizzaFactory() = default;
            void createPizza(PizzaType type, PizzaSize size);
            void tryCreateIPizzas(std::string command, std::vector<std::shared_ptr<IPizza>>& pizzas);

            class IPizzaFactoryException : public std::exception {
                public:
                    IPizzaFactoryException(const std::string &message) : _message(message) {}
                    const char *what() const noexcept override {
                        return _message.c_str();
                    }
                private:
                    std::string _message;
            };

        private:
            double _multiplier;
            std::map<std::string, PizzaType> _pizzaTypeMap = {
                {"margarita", PizzaType::Margarita},
                {"regina", PizzaType::Regina},
                {"americana", PizzaType::Americana},
                {"fantasia", PizzaType::Fantasia}
            };
            std::map<std::string, PizzaSize> _pizzaSizeMap = {
                {"S", PizzaSize::S},
                {"M", PizzaSize::M},
                {"L", PizzaSize::L},
                {"XL", PizzaSize::XL},
                {"XXL", PizzaSize::XXL}
            };
            std::map<PizzaType, std::function<std::shared_ptr<IPizza>(PizzaSize size, double multiplier)>> _pizzaFactory = {
                {PizzaType::Margarita, [](PizzaSize size, double multiplier) { return std::make_shared<Pizza::Margarita>(size, multiplier); }},
                {PizzaType::Regina, [](PizzaSize size, double multiplier) { return std::make_shared<Pizza::Regina>(size, multiplier); }},
                {PizzaType::Americana, [](PizzaSize size, double multiplier) { return std::make_shared<Pizza::Americana>(size, multiplier); }},
                {PizzaType::Fantasia, [](PizzaSize size, double multiplier) { return std::make_shared<Pizza::Fantasia>(size, multiplier); }},
            };
    };
}
