/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** NamedPipes
*/

#pragma once

#include <stdexcept>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

namespace plz {

    enum class PipeSide {
        None,
        ReadEnd,
        WriteEnd
    };

    class NamedPipes {
        public:
            NamedPipes(const std::string& path);
            ~NamedPipes();

            void open(PipeSide side)
            {
                if (this->_side != PipeSide::None)
                    return;
                if (side == PipeSide::ReadEnd) {
                    this->_in = std::ifstream(this->_path);
                    if (!this->_in.is_open())
                        throw std::runtime_error("Failed to open FIFO.");
                    this->_side = PipeSide::ReadEnd;
                }
                if (side == PipeSide::WriteEnd) {
                    this->_out = std::ofstream(this->_path);
                    if (!this->_out.is_open())
                        throw std::runtime_error("Failed to open FIFO.");
                    this->_side = PipeSide::WriteEnd;
                }
            }

            template<typename T>
            NamedPipes& operator<<(const T& in) {
                if (this->_side != PipeSide::WriteEnd)
                    throw std::runtime_error("Cannot write into that side of the pipe.");
                this->_out << in;
                return *this;
            }

            template<typename T>
            NamedPipes& operator>>(T& out) {
                if (this->_side != PipeSide::ReadEnd)
                    throw std::runtime_error("Cannot read into that side of the pipe.");
                this->_in >> out;
                return *this;
            }

            bool fail()
            {
                return this->_in.fail() || this->_out.fail();
            }

        protected:
        private:
            std::string _path = "";
            PipeSide _side = PipeSide::None;
            std::ifstream _in;
            std::ofstream _out;
            bool _fail = false;
    };

}
