/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** IpcTool
*/

#include "IpcTool.hpp"

plz::IpcTool::IpcTool(const std::string& channel, ProcessSide side) :
    _channel(channel), _side(side),
    _writePipe(channel + (side == plz::ProcessSide::Parent ? "_ptc" : "_ctp")),
    _readPipe(channel + (side == plz::ProcessSide::Parent ? "_ctp" : "_ptc"))
{
    if (this->_side == ProcessSide::None)
        throw std::runtime_error("Invalid None Ipc Side.");
    if (this->_side == ProcessSide::Parent) {
        this->_readPipe.open(plz::PipeSide::ReadEnd);
        this->_writePipe.open(plz::PipeSide::WriteEnd);
    } else {
        this->_writePipe.open(plz::PipeSide::WriteEnd);
        this->_readPipe.open(plz::PipeSide::ReadEnd);
    }
}

ssize_t plz::IpcTool::send(const plz::Packet& packet)
{
    return this->_writePipe.send(packet.raw(), packet.size());
}

ssize_t plz::IpcTool::send(const void *buf, size_t size)
{
    return this->_writePipe.send(buf, size);
}

plz::Packet plz::IpcTool::receive()
{
    plz::Packet packet;
    unsigned char byte = 0;

    while (this->_readPipe.receive(&byte, 1) > 0)
        packet.append(&byte, 1);
    return packet;
}

ssize_t plz::IpcTool::receive(void *buf, size_t size)
{
    return this->_readPipe.receive(buf, size);
}
