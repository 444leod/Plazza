/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Fork
*/

#include "Fork.hpp"

#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <thread>

plz::Fork::Fork()
{
    int parentPid = getpid();

    int pid = fork();
    if (pid == 0) {
        _parentPid = parentPid;
        _childPid = getpid();
    } else {
        _parentPid = parentPid;
        _childPid = pid;
    }
}

plz::Fork::~Fork()
{
    if (getpid() == _parentPid) {
        this->killFork();
    }
}

int plz::Fork::waitFork()
{
    if (getpid() != _parentPid)
        throw ForkException("waitFork can only be called by the parent process");

    int status;
    waitpid(_childPid, &status, 0);
    return status;
}

void plz::Fork::killFork()
{
    if (getpid() != _parentPid)
        throw ForkException("killFork can only be called by the parent process");

    kill(_childPid, SIGKILL);
}

bool plz::Fork::isChild() const
{
    return getpid() == _childPid;
}

pid_t plz::Fork::getChildPid() const
{
    return _childPid;
}

pid_t plz::Fork::getParentPid() const
{
    return _parentPid;
}
