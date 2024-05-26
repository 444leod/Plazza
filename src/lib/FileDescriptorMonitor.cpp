/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** FileDescriptorMonitor
*/

#include "FileDescriptorMonitor.hpp"

#include <iostream>

void lib::FileDescriptorMonitor::monitor(std::vector<int>& rdFds, std::vector<int>& wrFds, std::pair<std::chrono::seconds, std::chrono::milliseconds> timeout)
{
    if (rdFds.empty() && wrFds.empty())
        return;
    fd_set readFds;
    fd_set writeFds;
    struct timeval tv;
    int maxFd = 0;

    std::vector<int> tempReadFds;
    std::vector<int> tempWriteFds;


    FD_ZERO(&readFds);
    FD_ZERO(&writeFds);
    for (auto &fd : rdFds) {
        if (fd > maxFd)
            maxFd = fd;
        FD_SET(fd, &readFds);
        tempReadFds.push_back(fd);
    }
    for (auto &fd : wrFds) {
        if (fd > maxFd)
            maxFd = fd;
        FD_SET(fd, &writeFds);
        tempWriteFds.push_back(fd);
    }
    rdFds.clear();
    wrFds.clear();
    tv.tv_sec = timeout.first.count();
    tv.tv_usec = timeout.second.count();
    if (select(maxFd + 1, &readFds, &writeFds, NULL, &tv) < 0)
        throw std::runtime_error("select failed.");
    for (auto &fd : tempReadFds) {
        if (FD_ISSET(fd, &readFds))
            rdFds.push_back(fd);
    }
    for (auto &fd : tempReadFds) {
        if (FD_ISSET(fd, &writeFds))
            wrFds.push_back(fd);
    }
}
