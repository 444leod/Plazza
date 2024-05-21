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
        ThreadPool(int num_threads);
        ~ThreadPool();
        void Start();
        void QueueJob(const std::function<void()>& job);
        void Stop();
        bool Busy();

    private:
        void ThreadLoop();

        bool _should_terminate = false;
        std::mutex _queue_mutex;
        std::condition_variable _mutex_condition;
        std::vector<std::thread> _threads;
        std::queue<std::function<void()>> _jobs;
};