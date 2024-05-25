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
    std::size_t size = packet.size();
    return (this->_writePipe.send(reinterpret_cast<void *>(&size), sizeof(std::size_t)) +
            this->_writePipe.send(packet.raw(), packet.size()));
}

ssize_t plz::IpcTool::send(const void *buf, size_t size)
{
    return this->_writePipe.send(buf, size);
}

plz::Packet plz::IpcTool::receive()
{
    uint8_t byte = 0;
    std::size_t size = 0;
    plz::Packet packet;

    auto r = this->_readPipe.receive(&size, sizeof(size_t));
    if (r <= 0) return packet;

    for (std::size_t i = 0; i < size; i++) {
        r = this->_readPipe.receive(&byte, 1);
        if (r <= 0) return packet;
        packet.append(&byte, 1);
    }
    return packet;
}

ssize_t plz::IpcTool::receive(void *buf, size_t size)
{
    return this->_readPipe.receive(buf, size);
}

/**
 * This is a send and receive example:

    if (fork() == 0) {          // CHILD

        int tries = 10;
        usleep(1000 * 1000);
        plz::IpcTool ipc("fifo", plz::ProcessSide::Child);

        while (tries > 0) {
            usleep(100 * 1000);
            tries--;

            auto packet = ipc.receive();
            if (packet.size() == 0) continue;

            std::string a = "";
            packet >> a;
            std::cout << "Received: " << a << std::endl;
            tries = 10;
        }
        exit(0);

    } else {                    // PARENT

        plz::Pizza::Fantasia piz(plz::M, 1.0);
        plz::IpcTool ipc("fifo", plz::ProcessSide::Parent);

        plz::Packet packet;

        packet = plz::Packet();
        packet << "Hello world!";
        ipc.send(packet);

        packet = plz::Packet();
        packet << "And hi Leo!";
        ipc.send(packet);

        packet = plz::Packet();
        packet << "This is fun!";
        ipc.send(packet);
    }

*/
