#include "../../../include/partition_threads/with_thread_pool/thread_pool_impl/BasePartitionThreadPool.h"

BasePartitionThreadPool::BasePartitionThreadPool(const std::vector<int>& basicNumbers, int n, int m)
    : PartitionThreadPoolAbstract(basicNumbers, n, m) { 
    stop = false;
    for (int i = 0; i < m; ++i) {
        threadPool.emplace_back(&BasePartitionThreadPool::workerThread, this);
    }
}

BasePartitionThreadPool::~BasePartitionThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }
    condition.notify_all();

    for (std::thread& thread : threadPool) {
        thread.join(); 
    }
}

void BasePartitionThreadPool::addTask(const std::function<void()>& task) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        taskQueue.push(task);
    }
    condition.notify_one();
}

void BasePartitionThreadPool::workerThread() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this] { return !taskQueue.empty() || stop; });

            if (stop && taskQueue.empty()) {
                return;
            }

            task = std::move(taskQueue.front());
            taskQueue.pop();
        }
        task();
    }
}

std::vector<int> BasePartitionThreadPool::findPrimes() {
    auto startTimer = std::chrono::high_resolution_clock::now();

    int rangeSize = n - std::sqrt(n) + 1;
    std::vector<bool> isPrimeFlags(rangeSize, true);

    int basicRangeSize = basicNumbers.size() / m;
    int basicStart = 0;

    for (int i = 0; i < m; ++i) {
        int basicEnd = (i == m - 1) ? basicNumbers.size() : (basicStart + basicRangeSize);

        addTask([this, i, basicStart, basicEnd, &isPrimeFlags]() {
            processRange(basicNumbers, basicStart, basicEnd, isPrimeFlags);
            });

        basicStart = basicEnd;
    }

    {
        std::unique_lock<std::mutex> lock(queueMutex);
        condition.wait(lock, [this] { return taskQueue.empty(); });
    }

    std::vector<int> primes;
    int sqrtN = std::sqrt(n);
    for (int i = 0; i < rangeSize - 1; ++i) {
        if (isPrimeFlags[i]) {
            primes.push_back(sqrtN + i);
        }
    }

    auto endTimer = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration<double>(endTimer - startTimer).count();

    return primes;
}

void BasePartitionThreadPool::processRange(const std::vector<int>& localBasicNumbers, int rangeStart, int rangeEnd, std::vector<bool>& isPrimeFlags) {
    int sqrtN = std::sqrt(n);
    for (int num = sqrtN; num < n; ++num) {
        if (isPrimeFlags[num - sqrtN]) {
            for (int i = rangeStart; i < rangeEnd; ++i) {
                int base = localBasicNumbers[i];
                if (base * base > num) break; // Достаточно проверять до sqrt(num)

                if (num % base == 0) {
                    // Число не простое
                    isPrimeFlags[num - sqrtN] = false;
                    break;
                }
            }
        }
    }
}