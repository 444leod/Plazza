/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ThreadPool
*/

#include "ThreadPool.hpp"


ThreadPool::ThreadPool(std::uint32_t num_threads)
    : _num_threads(num_threads)
{
}

ThreadPool::~ThreadPool()
{
    Stop();
}

void ThreadPool::Start() {
    for (uint32_t i = 0; i < _num_threads; ++i) {
        _threads.emplace_back(std::thread(&ThreadPool::ThreadLoop, this));
    }
}

void ThreadPool::QueueJob(const std::function<void()>& job) {
    {
        std::unique_lock<std::mutex> lock(_queue_mutex);
        _jobs.push(job);
    }
    _mutex_condition.notify_one();
}

bool ThreadPool::Busy() {
    bool poolbusy;
    {
        std::unique_lock<std::mutex> lock(_queue_mutex);
        poolbusy = !_jobs.empty();
    }
    return poolbusy;
}

void ThreadPool::Stop() {
    {
        std::unique_lock<std::mutex> lock(_queue_mutex);
        _should_terminate = true;
    }
    _mutex_condition.notify_all();
    for (auto& thread : _threads) {
        thread.join();
    }
    _threads.clear();
}
