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
            void open(PipeSide side);

            /**
             * @brief Sends data through a NamedPipe.
            */
            ssize_t send(const void *buf, size_t size);

            /**
             * @brief Reads from a named pipe.
            */
            ssize_t receive(void *buf, size_t size);

           bool is_open() const { return this->_is_open; }

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
                return *this;
            }

        protected:
        private:
            int _fd = 0;
            std::string _path = "";
            PipeSide _side = PipeSide::None;
            bool _is_open = false;
    };

}
