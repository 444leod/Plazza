/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** APizzaFactory
*/

#include "IPizza.hpp"
#include "Margarita.hpp"
#include "Regina.hpp"
#include "Americana.hpp"
#include "Fantasia.hpp"

#include <memory>
#include <map>
#include <functional>

#pragma once

namespace plz {
    class IPizzaFactory {
        public:
            IPizzaFactory() {};
            ~IPizzaFactory() = default;
            // void tryCreateIPrimitive(std::string key, PizzaType& type, std::vector<std::shared_ptr<IPrimitive>>& primitives);

        private:
            std::map<std::string, PizzaType> _pizzaTypeMap = {
                {"margarita", PizzaType::Margarita},
                {"regina:", PizzaType::Regina},
                {"americana", PizzaType::Americana},
                {"fantasia", PizzaType::Fantasia}
            };
            std::map<PizzaType, std::function<std::shared_ptr<IPizza>(PizzaSize size, double multiplier)>> _primitiveFactory = {
                {PizzaType::Margarita, [](PizzaSize size, double multiplier) { return std::make_shared<Pizza::Margarita>(size, multiplier); }},
                {PizzaType::Regina, [](PizzaSize size, double multiplier) { return std::make_shared<Pizza::Regina>(size, multiplier); }},
                {PizzaType::Americana, [](PizzaSize size, double multiplier) { return std::make_shared<Pizza::Americana>(size, multiplier); }},
                {PizzaType::Fantasia, [](PizzaSize size, double multiplier) { return std::make_shared<Pizza::Fantasia>(size, multiplier); }},
            };
    };
}