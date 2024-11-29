#ifndef BASEPARTITIONTHREADPOOL_H
#define BASEPARTITIONTHREADPOOL_H

#include "PartitionThreadPoolAbstract.h"
#include <cmath>

class BasePartitionThreadPool : public PartitionThreadPoolAbstract {
public:
    BasePartitionThreadPool(const std::vector<int>& basicNumbers, int n, int m);
    ~BasePartitionThreadPool();
    double duration;

    std::vector<int> findPrimes() override;
    void addTask(const std::function<void()>& task) override;
    void workerThread() override;

private:
    void processRange(const std::vector<int>& localBasicNumbers, int rangeStart, int rangeEnd, std::vector<bool>& isPrimeFlags);
};

#endif
