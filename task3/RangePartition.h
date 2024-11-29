#ifndef RANGE_PARTITION_H
#define RANGE_PARTITION_H

#include "PartitionAbstract.h"
#include <vector>
#include <cmath>

class RangePartition : public PartitionAbstract {
public:
    RangePartition(const std::vector<int>& basicNumbers, int n, int m)
        : PartitionAbstract(basicNumbers, n, m), duration(0.0) {}

    std::vector<int> findPrimes() override;

    double duration;

private:
    void processRange(int start, int end, std::vector<int>& primes);
};

#endif
