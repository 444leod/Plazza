/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** IpcTool
*/

#pragma once

#include <NamedPipes.hpp>

namespace plz {

    enum class ProcessSide {
        None,
        Parent,
        Child
    };

    class IpcTool {
        public:
            IpcTool(const std::string& channel, ProcessSide side);
            ~IpcTool() = default;

            const std::string& channel() { return this->_channel; }
            ProcessSide side() { return this->_side; }

        protected:
        private:
            const std::string& _channel;
            ProcessSide _side;
            NamedPipes _readPipe;
            NamedPipes _writePipe;
    };
}
