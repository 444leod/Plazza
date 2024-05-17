/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** IpcTool
*/

#pragma once

#include <NamedPipes.hpp>

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
             * @brief Gets the write end of the IpcTool.
             * @return A reference to the `NamedPipe` used for writing.
            */
            NamedPipes& write() { return this->_writePipe; }

            /**
             * @brief Gets the read end of the IpcTool.
             * @return A reference to the `NamedPipe` used for reading.
            */
            NamedPipes& read() { return this->_readPipe; }

        protected:
        private:
            const std::string& _channel;
            ProcessSide _side;
            NamedPipes _readPipe;
            NamedPipes _writePipe;
    };
}
