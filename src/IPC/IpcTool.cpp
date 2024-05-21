/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** IpcTool
*/

#include "IpcTool.hpp"

plz::IpcTool::IpcTool(const std::string& channel, ProcessSide side)
    : _channel(channel), _side(side)
{
    if (this->_side == ProcessSide::None)
        throw std::runtime_error("Invalid None Ipc Side.");
    if (this->_side == ProcessSide::Parent) {
        this->_writePipe = NamedPipes(channel + "_ptc");
        this->_readPipe = NamedPipes(channel + "_ctp");
        this->_readPipe.open(plz::PipeSide::ReadEnd);
        this->_writePipe.open(plz::PipeSide::WriteEnd);
    } else {
        this->_writePipe = NamedPipes(channel + "_ctp");
        this->_readPipe = NamedPipes(channel + "_ptc");
        this->_writePipe.open(plz::PipeSide::WriteEnd);
        this->_readPipe.open(plz::PipeSide::ReadEnd);
    }
}

void plz::IpcTool::send(const void *buf, size_t size)
{
    return this->_writePipe.send(buf, size);
}

void plz::IpcTool::receive(void *buf, size_t size)
{
    return this->_readPipe.receive(buf, size);
}