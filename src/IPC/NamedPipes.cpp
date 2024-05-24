/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** NamedPipes
*/

#include "NamedPipes.hpp"
#include "errno.h"
#include <string.h>

plz::NamedPipes::NamedPipes(const std::string& path) : _path(path)
{
    ::mkfifo(this->_path.c_str(), 0666);
}

plz::NamedPipes::~NamedPipes()
{
    ::close(this->_fd);
    ::remove(this->_path.c_str());
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

ssize_t plz::NamedPipes::send(const void *buf, size_t size)
{
    ssize_t s = 0;

    if (!this->_is_open)
        throw std::runtime_error("NamedPipe not open.");

    if ((s = ::write(this->_fd, buf, size)) < 0)
        throw std::runtime_error("Could not write properly.");
    return s;
}

ssize_t plz::NamedPipes::receive(void *buf, size_t size)
{
    ssize_t s = 0;

    if (!this->_is_open)
        throw std::runtime_error("NamedPipe not open.");
    if (this->empty())
        return 0;
    if ((s = ::read(this->_fd, buf, size)) < 0)
        throw std::runtime_error("Could not read properly.");
    return s;
}

bool plz::NamedPipes::empty() const
{
    fd_set readfds;
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&readfds);
    FD_SET(this->_fd, &readfds);

    if (select(this->_fd + 1, &readfds, NULL, NULL, &tv) < 0) {
        std::cout << "select failed (" << strerror(errno) << ")" << std::endl;
        throw std::runtime_error("Select failed.");
    }
    return !FD_ISSET(this->_fd, &readfds);
}
