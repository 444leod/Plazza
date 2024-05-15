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

plz::NamedPipes::~NamedPipes()
{
}
