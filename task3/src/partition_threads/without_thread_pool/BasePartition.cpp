#include "../../../include/partition_threads/without_thread_pool/BasePartition.h"

#include <thread>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <iostream>


std::vector<int> BasePartition::findPrimes() {
    auto startTimer = std::chrono::high_resolution_clock::now();

    int rangeSize = n - std::sqrt(n) + 1;
    std::vector<bool> isPrimeFlags(rangeSize, true);

    std::vector<std::thread> threads;
    int basicRangeSize = basicNumbers.size() / m;
    int basicStart = 0;

    for (int i = 0; i < m; ++i) {
        int basicEnd = (i == m - 1) ? basicNumbers.size() : (basicStart + basicRangeSize);

        threads.emplace_back(&BasePartition::processRange, this,
            std::ref(basicNumbers), basicStart, basicEnd, std::ref(isPrimeFlags));
        basicStart = basicEnd;
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // Извлечение простых чисел из флагов
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

void BasePartition::processRange(const std::vector<int>& localBasicNumbers, int rangeStart, int rangeEnd, std::vector<bool>& isPrimeFlags) {
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



















































// Более читаемая версия метода. Работает медленнее из-за стекового фрейма

//// Вызов функции сильно замедляет код
//
//bool BasePartition::isNumberPrime(int num, const std::vector<int>& localBasicNumbers, int rangeStart, int rangeEnd) {
//    for (int i = rangeStart; i < rangeEnd; ++i) {
//        int base = localBasicNumbers[i];
//        if (base * base > num) break; // Достаточно проверять до sqrt(num)
//        if (num % base == 0) {
//            // Число не простое
//            return false;
//        }
//    }
//    return true;
//}
//
//
//void BasePartition::processRange(const std::vector<int>& localBasicNumbers, int rangeStart, int rangeEnd, std::vector<bool>& isPrimeFlags) {
//    int sqrtN = std::sqrt(n);
//    for (int num = sqrtN; num < n; ++num) {
//        if (isPrimeFlags[num - sqrtN]) {
//            isPrimeFlags[num - sqrtN] = isNumberPrime(num, localBasicNumbers, rangeStart, rangeEnd);
//        }
//    }
//}