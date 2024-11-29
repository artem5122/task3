#ifndef RANGE_PARTITION_THREAD_POOL_H
#define RANGE_PARTITION_THREAD_POOL_H

#include "PartitionThreadPoolAbstract.h"
#include <vector>
#include <cmath>

class RangePartitionThreadPool : public PartitionThreadPoolAbstract {
public:
    RangePartitionThreadPool(const std::vector<int>& basicNumbers, int n, int m);
    ~RangePartitionThreadPool();
    double duration;

    std::vector<int> findPrimes() override;
    void addTask(const std::function<void()>& task) override;
    void workerThread() override;

private:
    void processRange(int start, int end, std::vector<int>& primes);
};

#endif
