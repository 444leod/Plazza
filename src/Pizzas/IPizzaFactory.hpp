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
#include <vector>
#include <functional>
#include <sstream>

#pragma once

namespace plz {
    class IPizzaFactory {
        public:
            IPizzaFactory() {};
            ~IPizzaFactory() = default;
            void tryCreateIPizzas(std::string command, std::vector<std::shared_ptr<IPizza>>& pizzas);

            class IPizzaFactoryException : public std::exception {
                public:
                    IPizzaFactoryException(const std::string &message)
                    {
                        std::stringstream ss;
                        ss << "IPizzaFactoryException: " << message;
                        _message = ss.str();
                    }
                    const char *what() const noexcept override {
                        return _message.c_str();
                    }
                private:
                    std::string _message;
            };

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