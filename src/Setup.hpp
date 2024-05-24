/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Setup
*/

#pragma once

#include <cstdint>
#include <exception>
#include <string>

namespace plz {
    class SetupException : public std::exception {
        public:
            SetupException() = default;
            SetupException(const std::string& what) : _what(what) {}
            ~SetupException() = default;
            virtual const char *what() const noexcept { return this->_what.c_str(); }
        private:
            std::string _what = "Unknwon exception during setup.";
    };

    class Setup {
        public:
            Setup() = default;
            Setup(int ac, char **av);
            ~Setup() = default;

            double multiplier() const { return this->_multiplier; }
            std::uint32_t pizzaiolos() const { return this->_pizzaiolos; }
            std::uint32_t restock() const { return this->_restock; }

            const Setup& operator=(const Setup& other);

        protected:
        private:
            double _multiplier;
            std::uint32_t _pizzaiolos;
            std::uint32_t _restock;
    };
}
