/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** FileDescriptorMonitor
*/

#pragma once

#include <vector>
#include <chrono>
#include <optional>

namespace lib  {
    class FileDescriptorMonitor {
        public:
            FileDescriptorMonitor() = default;
            ~FileDescriptorMonitor() = default;

            void monitor(std::vector<int>& readFds, std::vector<int>& writeFds, std::pair<std::chrono::seconds, std::chrono::milliseconds> timeout = std::pair<std::chrono::seconds, std::chrono::milliseconds>(0, 0));
    };
}
