#include "RangePartition.h"
#include <vector>
#include <thread>
#include <cmath>
#include <algorithm>
#include <iostream>



std::vector<int> RangePartition::findPrimes() {
    auto startTimer = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;                  
    std::vector<std::vector<int>> threadResults(m); // ������� ����������� ��� ������� ������
    int rangeSize = (n - std::sqrt(n)) / m;            
    int start = std::sqrt(n);                      

    for (int i = 0; i < m; ++i) {
        int end = (i == m - 1) ? n : (start + rangeSize - 1);

        //��������� ��������� �� ����� processRange, ��������� �� ������� ������, ... 
        // � ������ �� ������ primes (����� �� ����������)
        // & ������������ � ������� ������� �������, std::ref � �������, �������
        threads.emplace_back(&RangePartition::processRange, this, start, end, std::ref(threadResults[i]));
        start += rangeSize; 
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // ������������ �����������
    std::vector<int> primes;
    for (const auto& localPrimes : threadResults) {
        primes.insert(primes.end(), localPrimes.begin(), localPrimes.end());
    }
    std::sort(primes.begin(), primes.end());


    auto endTimer = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration<double>(endTimer - startTimer).count();
    return primes;
}


// ����� ��� ������ ������� ����� � ��������� ���������
void RangePartition::processRange(int start, int end, std::vector<int>& localPrimes) {
    for (int num = start; num <= end; ++num) {
        bool isPrime = true;
        for (const auto& base : basicNumbers) {
            if (base * base > num) break; // ���������� ��������� �������� �� sqrt(num)
            if (num % base == 0) {
                isPrime = false; // ����� �� �������
                break;
            }
        }
        if (isPrime) {
            localPrimes.push_back(num); 
        }
    }
}

