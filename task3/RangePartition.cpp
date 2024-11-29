#include "RangePartition.h"
#include <vector>
#include <thread>
#include <cmath>
#include <algorithm>
#include <iostream>



std::vector<int> RangePartition::findPrimes() {
    auto startTimer = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;                  
    std::vector<std::vector<int>> threadResults(m); // Векторы результатов для каждого потока
    int rangeSize = (n - std::sqrt(n)) / m;            
    int start = std::sqrt(n);                      

    for (int i = 0; i < m; ++i) {
        int end = (i == m - 1) ? n : (start + rangeSize - 1);

        //Передаётся указатель на метод processRange, указатель на текущий объект, ... 
        // и ссылка на вектор primes (чтобы не копировать)
        // & используется в обычных вызовах функций, std::ref в потоках, лямбдах
        threads.emplace_back(&RangePartition::processRange, this, start, end, std::ref(threadResults[i]));
        start += rangeSize; 
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // Конкатенация результатов
    std::vector<int> primes;
    for (const auto& localPrimes : threadResults) {
        primes.insert(primes.end(), localPrimes.begin(), localPrimes.end());
    }
    std::sort(primes.begin(), primes.end());


    auto endTimer = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration<double>(endTimer - startTimer).count();
    return primes;
}


// Метод для поиска простых чисел в указанном диапазоне
void RangePartition::processRange(int start, int end, std::vector<int>& localPrimes) {
    for (int num = start; num <= end; ++num) {
        bool isPrime = true;
        for (const auto& base : basicNumbers) {
            if (base * base > num) break; // Достаточно проверять делители до sqrt(num)
            if (num % base == 0) {
                isPrime = false; // Число не простое
                break;
            }
        }
        if (isPrime) {
            localPrimes.push_back(num); 
        }
    }
}

