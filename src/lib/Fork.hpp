/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Fork
*/

#pragma once

#include <unistd.h>
#include <exception>
#include <string>

namespace plz  {
    class Fork {
        public:
            Fork();
            ~Fork();
            int waitFork();
            void killFork();
            bool isChild() const;
            pid_t getChildPid() const;
            pid_t getParentPid() const;

            class ForkException : public std::exception {
                public:
                    ForkException(std::string const &message) : _message(message) {};
                    ForkException() = default;
                    virtual ~ForkException() = default;
                    virtual const char *what() const noexcept { return _message.data(); }
                private:
                    std::string _message = "Fork error";
            };

        private:
            pid_t _parentPid;
            pid_t _childPid;
    };
}
