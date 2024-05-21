/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** NamedPipes
*/

#include "NamedPipes.hpp"

plz::NamedPipes::NamedPipes(const std::string& path) : _path(path)
{
    mkfifo(this->_path.c_str(), 0666);
}

void plz::NamedPipes::open(plz::PipeSide side)
{
    if (this->_side != PipeSide::None || side == PipeSide::None)
        return;
    this->_side = side;
    auto flags = side == PipeSide::ReadEnd ? O_RDONLY : O_WRONLY;
    this->_fd = ::open(this->_path.c_str(), flags);
    if (this->_fd < 0)
        throw std::runtime_error("Could not open fifo.");
    else
        this->_is_open = true;
}

void plz::NamedPipes::send(const void *buf, size_t size)
{
    if (!this->_is_open) {
        throw std::runtime_error("NamedPipe not open.");
        return;
    }
    if (::write(this->_fd, buf, size) < 0)
        throw std::runtime_error("Could not write properly.");
}

void plz::NamedPipes::receive(void *buf, size_t size)
{
    if (!this->_is_open) {
        throw std::runtime_error("NamedPipe not open.");
        return;
    }
    if (::read(this->_fd, buf, size) < 0)
        throw std::runtime_error("Could not read properly.");
}