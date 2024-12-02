#pragma once
#include "../PartitionAbstract.h"
#include <vector>
#include <string>
#include <mutex>
#include <cmath>

class BasePartition : public PartitionAbstract {
public:
    BasePartition(const std::vector<int>& basicNumbers, int n, int m)
        : PartitionAbstract(basicNumbers, n, m), duration(0.0) {}

    std::vector<int> findPrimes() override;

    double duration;

private:
    void processRange(const std::vector<int>& localBasicNumbers, int rangeStart, int rangeEnd, std::vector<bool>& isPrimeFlags);
    bool isNumberPrime(int num, const std::vector<int>& localBasicNumbers, int rangeStart, int rangeEnd);

    std::mutex flagMutex;
};
