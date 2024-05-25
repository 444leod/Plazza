/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ThreadPoolExemple
*/

#include "../src/ThreadPool.hpp"

#include <iostream>

int main()
{
    ThreadPool pool(4);

    pool.Start();

    for (int i = 0; i < 10; ++i) {
        pool.QueueJob([i] {
            // COOK PIZZAS HERE!!
            std::cout << "Job " << i << " started" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Job " << i << " finished" << std::endl;
        });
    }

    while (pool.Busy()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << pool.OccupiedThreads() << " threads are busy" << std::endl;
    }

    std::cout << pool.OccupiedThreads() << " threads are busy" << std::endl;
    pool.Stop();

    return 0;
}
