/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** IpcTool
*/

#pragma once

#include "Packet.hpp"
#include "NamedPipes.hpp"

namespace plz {

    /**
     * @brief The side of the IPC on which the process stands.
    */
    enum class ProcessSide {
        None,
        Parent,
        Child
    };

    /**
     * @brief IpcTools are a two-way communication tool.
     * You set it up after process forked away from each-other.
     * You reference their side, and the channel with which they communicate.
    */
    class IpcTool {
        public:
            /**
             * @param channel The prefix of the FIFOs' names used for communication.
             * @param side The side on which the process stands.
            */
            IpcTool(const std::string& channel, ProcessSide side);
            ~IpcTool() = default;

            /**
             * @brief Gets the channel prefix.
             * @return A std::string containing the channel prefix.
            */
            const std::string& channel() const { return this->_channel; }

            /**
             * @brief Gets the side of the (process's) IpcTool.
             * @return A ProcessSide value.
            */
            ProcessSide side() const { return this->_side; }

            /**
             * @brief Sends a packet
            */
            ssize_t send(const Packet& packet);

            /**
             * @brief Sends a buffer through Named Pipes.
             *
             * @param buf The data buffer to send.
             * @param size The size of the buffer in bytes.
            */
            ssize_t send(const void *buf, size_t size);


            /**
             * @brief Reads a packet
            */
            Packet receive();

            /**
             * @brief Reads from a Named Pipe into a buffer of a given size.
             *
             * @param buf The buffer to put the read data into.
             * @param size The amount of data to read in bytes.
            */
            ssize_t receive(void *buf, size_t size);

        protected:
        private:
            const std::string& _channel;
            ProcessSide _side;
            NamedPipes _writePipe;
            NamedPipes _readPipe;
    };
}
