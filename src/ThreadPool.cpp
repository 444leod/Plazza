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
    : _numThreads(num_threads)
{
}

/*
 * @brief Destroy the ThreadPool::ThreadPool object and stop all threads
*/
ThreadPool::~ThreadPool()
{
    stop();
}

/*
 * @brief Start all threads in the pool and give them basic the threadLoop
*/
void ThreadPool::start() {
    for (uint32_t i = 0; i < this->_numThreads; ++i) {
        this->_threads.emplace_back(std::thread(&ThreadPool::threadLoop, this));
    }
}

/*
 * @brief Queue a job to be executed by the thread pool
 * @param job The job to be executed
*/
void ThreadPool::queueJob(const std::function<void()>& job) {
    {
        std::unique_lock<std::mutex> lock(this->_queueMutex);
        this->_jobs.push(job);
    }
    this->_mutexCondition.notify_one();
}

/*
 * @brief Check if the thread pool is busy
 * @return true if the thread pool is busy else false
*/
bool ThreadPool::busy() {
    bool poolbusy;
    {
        std::unique_lock<std::mutex> lock(this->_queueMutex);
        poolbusy = !this->_jobs.empty();
    }
    return poolbusy;
}

/*
 * @brief Stop all threads in the pool by joining them
 * @detail This function will block until all threads are joined, meaning that they wait for all jobs to finish
*/
void ThreadPool::stop() {
    {
        std::unique_lock<std::mutex> lock(this->_queueMutex);
        this->_shouldTerminate = true;
    }
    this->_mutexCondition.notify_all();
    for (auto& thread : this->_threads) {
        thread.join();
    }
    this->_threads.clear();
}

/*
 * @brief Get the number of threads that are currently occupied
 * @return The number of threads that are currently occupied
*/
std::uint32_t ThreadPool::occupiedThreads() const {
    return this->_numOccupiedThreads;
}

/*
 * @brief The main loop for the threads in the pool
*/
void ThreadPool::threadLoop() {
    while (1) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(this->_queueMutex);
            this->_mutexCondition.wait(lock, [this] {
                return !this->_jobs.empty() || this->_shouldTerminate;
            });
            if (this->_shouldTerminate) {
                return;
            }
            this->_numOccupiedThreads++;
            job = this->_jobs.front();
            this->_jobs.pop();
        }
        job();
        {
            std::unique_lock<std::mutex> lock(this->_queueMutex);
            this->_numOccupiedThreads--;
        }
    }
}
