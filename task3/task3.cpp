﻿#include "EratosthenesSieve.h"
#include "NumbersGenerator.h"
#include "RangePartition.h"
#include "BasePartition.h"
#include "RangePartitionThreadPool.h"
#include "BasePartitionThreadPool.h"
#include "FoundPrimes.h"
#include <iostream>
#include <vector>

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 65001 > nul");


    int n, m;
    std::cout << "Введите n (граница диапазона): ";
    std::cin >> n;
    std::cout << "Введите m (количество потоков): ";
    std::cin >> m;


    std::vector<int> numbers = NumbersGenerator::generateNumbers(n);
    std::vector<int> basicNumbers = EratosthenesSieve::getBasicNumbers(numbers);
    std::vector<int> primes;
        

    RangePartition rangePartition(basicNumbers, n, m);
    primes = rangePartition.findPrimes();
    std::cout << "Время выполнения: " << rangePartition.duration << std::endl;


    BasePartition basePartition(basicNumbers, n, m);
    primes = basePartition.findPrimes();
    std::cout << "Время выполнения: " << basePartition.duration << std::endl;


    RangePartitionThreadPool rangePartitionTP(basicNumbers, n, m);
    primes = rangePartitionTP.findPrimes();
    std::cout << "Время выполнения: " << rangePartitionTP.duration << std::endl;


    BasePartitionThreadPool basePartitionTP(basicNumbers, n, m);
    primes = basePartitionTP.findPrimes();
    std::cout << "Время выполнения: " << basePartitionTP.duration << std::endl;


    FoundPrimes foundprimes(basicNumbers, primes);
    foundprimes.printToConsole();

    return 0;
}
