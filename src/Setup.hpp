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
            Setup(int ac, char **av)
            {
                if (ac != 4)
                    throw SetupException("Bad argument count.");
                auto m = std::stod(av[1]);
                auto c = std::stoi(av[2]);
                auto r = std::stoi(av[3]);
                if (m <= 0)
                    throw SetupException("Multiplier cannot be negative or zero.");
                if (c < 0)
                    throw SetupException("Cannot have negative amount of cooks.");
                if (r < 0)
                    throw SetupException("Restock time cannot be negative.");
                this->_multiplier = m;
                this->_cooks = c;
                this->_restock = r;
            }
            ~Setup() = default;

            double multiplier() const { return this->_multiplier; }
            std::uint32_t cooks() const { return this->_cooks; }
            std::uint32_t restock() const { return this->_restock; }

            const Setup& operator=(const Setup& other)
            {
                this->_multiplier = other.multiplier();
                this->_cooks = other.cooks();
                this->_restock = other.restock();
                return *this;
            };

        protected:
        private:
            double _multiplier;
            std::uint32_t _cooks;
            std::uint32_t _restock;
    };
}
