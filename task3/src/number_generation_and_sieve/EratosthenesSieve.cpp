#include "../../include/number_generation_and_sieve/EratosthenesSieve.h"


std::vector<int> EratosthenesSieve::getBasicNumbers(std::vector<int> numbers)
{
    int n = std::sqrt(numbers.size());
    for (int i = 2; i < n; i++) {
        if (numbers[i] != 0) {
            for (int j = i * i; j < n; j += i) {
                numbers[j] = 0;
            } 
        }
    }

    std::vector<int> basicNumbers;
    for (int i = 2; i < n; i++) {
        if (numbers[i] != 0) {
            basicNumbers.push_back(i);
        }
    }

    return basicNumbers;
}