#pragma once
#include <vector>

class PartitionAbstract {
public:
    PartitionAbstract(const std::vector<int>& basicNumbers, int n, int m)
        : basicNumbers(basicNumbers), n(n), m(m) {}

    virtual ~PartitionAbstract() = default;

    virtual std::vector<int> findPrimes() = 0;

protected:
    const std::vector<int>& basicNumbers;
    int n;
    int m;
};
