/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** FileDescriptorMonitor
*/

#include "FileDescriptorMonitor.hpp"

lib::FileDescriptorMonitor::FileDescriptorMonitor()
{
}

lib::FileDescriptorMonitor::FileDescriptorMonitor(std::vector<int> readFds, std::vector<int> writeFds, std::optional<std::pair<std::chrono::seconds, std::chrono::milliseconds>> timeout) : _readFds(readFds), _writeFds(writeFds), _timeout(timeout)
{
}

lib::FileDescriptorMonitor::~FileDescriptorMonitor()
{
}

void lib::FileDescriptorMonitor::watch()
{
    if (_readFds.empty() && _writeFds.empty())
        return;
    fd_set readFds;
    fd_set writeFds;
    struct timeval tv;
    int maxFd = 0;

    FD_ZERO(&readFds);
    FD_ZERO(&writeFds);
    for (auto &fd : _readFds) {
        if (fd > maxFd)
            maxFd = fd;
        FD_SET(fd, &readFds);
    }
    for (auto &fd : _writeFds) {
        if (fd > maxFd)
            maxFd = fd;
        FD_SET(fd, &writeFds);
    }
    if (_timeout.has_value()) {
        tv.tv_sec = _timeout.value().first.count();
        tv.tv_usec = _timeout.value().second.count();
        select(maxFd + 1, &readFds, &writeFds, NULL, &tv);
    } else {
        select(maxFd + 1, &readFds, &writeFds, NULL, NULL);
    }
    for (auto &fd : _readFds) {
        if (FD_ISSET(fd, &readFds))
            _readableFds.push_back(fd);
    }
    for (auto &fd : _writeFds) {
        if (FD_ISSET(fd, &writeFds))
            _writableFds.push_back(fd);
    }
}

std::vector<int> lib::FileDescriptorMonitor::getReadFds() const
{
    return _readFds;
}

std::vector<int> lib::FileDescriptorMonitor::getWriteFds() const
{
    return _writeFds;
}

std::vector<int> lib::FileDescriptorMonitor::getReadableFds() const
{
    return _readableFds;
}

std::vector<int> lib::FileDescriptorMonitor::getWritableFds() const
{
    return _writableFds;
}

bool lib::FileDescriptorMonitor::isReadable(int fd) const
{
    return std::find(_readableFds.begin(), _readableFds.end(), fd) != _readableFds.end();
}

bool lib::FileDescriptorMonitor::isWritable(int fd) const
{
    return std::find(_writableFds.begin(), _writableFds.end(), fd) != _writableFds.end();
}

void lib::FileDescriptorMonitor::addReadFd(int fd)
{
    _readFds.push_back(fd);
}

void lib::FileDescriptorMonitor::addWriteFd(int fd)
{
    _writeFds.push_back(fd);
}

void lib::FileDescriptorMonitor::removeReadFd(int fd)
{
    _readFds.erase(std::remove(_readFds.begin(), _readFds.end(), fd), _readFds.end());
}

void lib::FileDescriptorMonitor::removeWriteFd(int fd)
{
    _writeFds.erase(std::remove(_writeFds.begin(), _writeFds.end(), fd), _writeFds.end());
}

void lib::FileDescriptorMonitor::setTimeout(std::pair<std::chrono::seconds, std::chrono::milliseconds> timeout)
{
    _timeout = timeout;
}

void lib::FileDescriptorMonitor::setTimeout(std::chrono::seconds seconds, std::chrono::milliseconds milliseconds)
{
    _timeout = std::make_pair(seconds, milliseconds);
}

void lib::FileDescriptorMonitor::setTimeout(std::chrono::seconds seconds)
{
    _timeout = std::make_pair(seconds, std::chrono::milliseconds(0));
}

void lib::FileDescriptorMonitor::setTimeout(std::chrono::milliseconds milliseconds)
{
    _timeout = std::make_pair(std::chrono::seconds(0), milliseconds);
}

void lib::FileDescriptorMonitor::removeTimeout()
{
    _timeout = std::nullopt;
}


