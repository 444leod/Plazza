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
        ThreadPool(std::uint32_t _numThreads);
        ~ThreadPool();
        void Start();
        void QueueJob(const std::function<void()>& job);
        void Stop();
        bool Busy();
        std::uint32_t OccupiedThreads() const;

    private:
        void ThreadLoop();

        std::uint32_t _numThreads;
        std::uint32_t _numOccupiedThreads = 0;
        bool _shouldTerminate = false;
        std::mutex _queueMutex;
        std::condition_variable _mutexCondition;
        std::vector<std::thread> _threads;
        std::queue<std::function<void()>> _jobs;
};