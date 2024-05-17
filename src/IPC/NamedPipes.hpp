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

    /**
     * @brief Represents a side of a Pipe.
    */
    enum class PipeSide {
        None,
        ReadEnd,
        WriteEnd
    };

    /**
     * @brief An encapsulation of an Unix FIFO.
    */
    class NamedPipes {
        public:
            NamedPipes() = default;
            /**
             * @param path The name of the FIFO to create.
            */
            NamedPipes(const std::string& path);
            ~NamedPipes() = default;

            /**
             * @brief Opens the FIFO for one side.
             * Use this to start using a NamedPipe.
            */
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

            /**
             * @brief Writes into a FIFO.
             *
             * @param in The content to write. This has to be writable to an ofstream.
             * @return A reference to the used NamedPipe.
            */
            template<typename T>
            NamedPipes& operator<<(const T& in) {
                if (this->_side != PipeSide::WriteEnd)
                    throw std::runtime_error("Cannot write into that side of the pipe.");
                this->_out << in;
                return *this;
            }

            /**
             * @brief Reads from a FIFO.
             *
             * @param out The content buffer to write into. This has to readable from an ofstream.
             * @return A reference to the used NamedPipe.
            */
            template<typename T>
            NamedPipes& operator>>(T& out) {
                if (this->_side != PipeSide::ReadEnd)
                    throw std::runtime_error("Cannot read into that side of the pipe.");
                this->_in >> out;
                return *this;
            }

            /**
             * @brief Set operator for NamedPipes.
             *
             * @param other The source NamedPipe to use.
             * @return A reference to the newly setup NamedPipe.
            */
            NamedPipes& operator=(const NamedPipes& other) {
                this->_path = other._path;
                this->_side = other._side;
                this->open(other._side);
                this->_fail = other._fail;
                return *this;
            }

            /**
             * @brief The state of the last FIFO operation.
             * @return `true` if failed to read or write. `false` otherwise.
            */
            bool fail() const { return this->_in.fail() || this->_out.fail(); }

        protected:
        private:
            std::string _path = "";
            PipeSide _side = PipeSide::None;
            std::ifstream _in;
            std::ofstream _out;
            bool _fail = false;
    };

}
