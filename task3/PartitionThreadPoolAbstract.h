#pragma once
#include "PartitionAbstract.h"
#include <vector>
#include <functional>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

class PartitionThreadPoolAbstract : public PartitionAbstract {
public:
    PartitionThreadPoolAbstract(const std::vector<int>& basicNumbers, int n, int m)
        : PartitionAbstract(basicNumbers, n, m), stop(false) {}

    virtual ~PartitionThreadPoolAbstract() = default;

    virtual std::vector<int> findPrimes() = 0;
    virtual void addTask(const std::function<void()>& task) = 0;
    virtual void workerThread() = 0;

protected:
    bool stop;
    std::vector<std::thread> threadPool;
    std::queue<std::function<void()>> taskQueue;
    std::mutex queueMutex;
    std::condition_variable condition;
};
