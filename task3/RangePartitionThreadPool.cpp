#include "RangePartitionThreadPool.h"
#include <algorithm>
#include <iostream>
#include <future>

RangePartitionThreadPool::RangePartitionThreadPool(const std::vector<int>& basicNumbers, int n, int m)
    : PartitionThreadPoolAbstract(basicNumbers, n, m) { 
    stop = false;  

    for (int i = 0; i < m; ++i) {
        threadPool.emplace_back(&RangePartitionThreadPool::workerThread, this);
    }
}


RangePartitionThreadPool::~RangePartitionThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread& thread : threadPool) {
        thread.join();
    }
}

void RangePartitionThreadPool::addTask(const std::function<void()>& task) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        taskQueue.push(task);
    }
    condition.notify_one();
}

// Ожидает появления новых задач
void RangePartitionThreadPool::workerThread() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this] { return !taskQueue.empty() || stop; });

            if (stop && taskQueue.empty())
                return;

            task = std::move(taskQueue.front());
            taskQueue.pop();
        }
        task();

        condition.notify_all();
    }
}

std::vector<int> RangePartitionThreadPool::findPrimes() {
    auto startTimer = std::chrono::high_resolution_clock::now();

    int rangeSize = (n - std::sqrt(n)) / m;
    int start = std::sqrt(n);
    std::vector<std::vector<int>> threadResults(m);
    std::mutex resultsMutex;

    // Добавление задач в тред пул
    for (int i = 0; i < m; ++i) {
        int end = (i == m - 1) ? n : (start + rangeSize - 1);

        addTask([this, start, end, &threadResults, i, &resultsMutex]() {
            std::vector<int> localPrimes;
            processRange(start, end, localPrimes);

            // Более эффективное присваивание значения. Без копирования
            threadResults[i] = std::move(localPrimes);
            });

        start += rangeSize;
    }

    // Ожидание завершения всех задач
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        condition.wait(lock, [this] { return taskQueue.empty(); });
    }

    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }
    // Уведомление всех ожидающих потоков
    condition.notify_all();

    for (std::thread& thread : threadPool) {
        thread.join();
    }

    std::vector<int> primes;
    for (const auto& localPrimes : threadResults) {
        primes.insert(primes.end(), localPrimes.begin(), localPrimes.end());
    }
    std::sort(primes.begin(), primes.end());

    auto endTimer = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration<double>(endTimer - startTimer).count();
    return primes;
}



void RangePartitionThreadPool::processRange(int start, int end, std::vector<int>& localPrimes) {
    for (int num = start; num <= end; ++num) {
        bool isPrime = true;
        for (const auto& base : basicNumbers) {
            if (base * base > num) break;
            if (num % base == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            localPrimes.push_back(num);
        }
    }
}
