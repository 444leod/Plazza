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
            FileDescriptorMonitor();
            FileDescriptorMonitor(std::vector<int> readFds, std::vector<int> writeFds, std::optional<std::pair<std::chrono::seconds, std::chrono::milliseconds>> timeout = std::nullopt);
            ~FileDescriptorMonitor();

            void watch();
            std::vector<int> getReadFds() const;
            std::vector<int> getWriteFds() const;
            std::vector<int> getReadableFds() const;
            std::vector<int> getWritableFds() const;
            bool isReadable(int fd) const;
            bool isWritable(int fd) const;
            void addReadFd(int fd);
            void addWriteFd(int fd);
            void removeReadFd(int fd);
            void removeWriteFd(int fd);
            void setTimeout(std::pair<std::chrono::seconds, std::chrono::milliseconds> timeout);
            void setTimeout(std::chrono::seconds seconds, std::chrono::milliseconds milliseconds);
            void setTimeout(std::chrono::seconds seconds);
            void setTimeout(std::chrono::milliseconds milliseconds);
            void removeTimeout();

        protected:
        private:
            std::vector<int> _readFds = {};
            std::vector<int> _writeFds = {};
            std::vector<int> _readableFds = {};
            std::vector<int> _writableFds = {};
            std::optional<std::pair<std::chrono::seconds, std::chrono::milliseconds>> _timeout = std::nullopt;
    };
}
