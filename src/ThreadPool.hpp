/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ThreadPool
*/

#pragma once

#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

class ThreadPool {
    public:
        ThreadPool(std::uint32_t numThreads);
        ~ThreadPool();
        void start();
        void queueJob(const std::function<void()>& job);
        void stop();
        bool busy();
        std::uint32_t occupiedThreads() const;

    private:
        void threadLoop();

        std::uint32_t _numThreads;
        std::uint32_t _numOccupiedThreads = 0;
        bool _shouldTerminate = false;
        std::mutex _queueMutex;
        std::condition_variable _mutexCondition;
        std::vector<std::thread> _threads;
        std::queue<std::function<void()>> _jobs;
};