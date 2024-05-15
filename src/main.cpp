/*
** EPITECH PROJECT, 2024
** main
** File description:
** main
*/

#include "macros.hpp"
#include "NamedPipes.hpp"

int main(UNUSED int argc, UNUSED char *argv[], UNUSED char *env[])
{
    std::string a = "";
    plz::NamedPipes pipe("fifo");

    if (fork() == 0) {
        pipe.open(plz::PipeSide::WriteEnd);
        std::cin >> a;
        pipe << getpid() << " a dit " << a;
    } else {
        pipe.open(plz::PipeSide::ReadEnd);
        while (true) {
            pipe >> a;
            if (pipe.fail()) break;
            std::cout << a << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
