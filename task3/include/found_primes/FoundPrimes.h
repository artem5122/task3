#pragma once
#include <vector>
#include <string>

class FoundPrimes {
public:
    FoundPrimes(const std::vector<int>& basicNumbers, const std::vector<int>& primeNumbers);
    void printToConsole();
    void printToFile(const std::string& filename);

private:
    std::vector<int> finalPrimeNumbers;
};
