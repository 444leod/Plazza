/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ThreadPool
*/

#include "ThreadPool.hpp"

/*
 * @brief Construct a new ThreadPool::ThreadPool object
 * @param num_threads Number of threads to create
*/
ThreadPool::ThreadPool(std::uint32_t num_threads)
    : _num_threads(num_threads)
{
}

/*
 * @brief Destroy the ThreadPool::ThreadPool object and stop all threads
*/
ThreadPool::~ThreadPool()
{
    Stop();
}

/*
 * @brief Start all threads in the pool and give them basic the ThreadLoop
*/
void ThreadPool::Start() {
    for (uint32_t i = 0; i < _num_threads; ++i) {
        _threads.emplace_back(std::thread(&ThreadPool::ThreadLoop, this));
    }
}

/*
 * @brief Queue a job to be executed by the thread pool
 * @param job The job to be executed
*/
void ThreadPool::QueueJob(const std::function<void()>& job) {
    {
        std::unique_lock<std::mutex> lock(_queue_mutex);
        _jobs.push(job);
    }
    _mutex_condition.notify_one();
}

/*
 * @brief Check if the thread pool is busy
 * @return true if the thread pool is busy else false
*/
bool ThreadPool::Busy() {
    bool poolbusy;
    {
        std::unique_lock<std::mutex> lock(_queue_mutex);
        poolbusy = !_jobs.empty();
    }
    return poolbusy;
}

/*
 * @brief Stop all threads in the pool by joining them
 * @detail This function will block until all threads are joined, meaning that they wait for all jobs to finish
*/
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

/*
 * @brief The main loop for the threads in the pool
*/
void ThreadPool::ThreadLoop() {
    while (1) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(_queue_mutex);
            _mutex_condition.wait(lock, [this] {
                return !_jobs.empty() || _should_terminate;
            });
            if (_should_terminate) {
                return;
            }
            job = _jobs.front();
            _jobs.pop();
        }
        job();
    }
}
