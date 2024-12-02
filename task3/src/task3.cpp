#include <iostream>
#include <vector>
#include "../include/number_generation_and_sieve/NumbersGenerator.h"
#include "../include/number_generation_and_sieve/EratosthenesSieve.h"
#include "../include/partition_threads/without_thread_pool/RangePartition.h"
#include "../include/partition_threads/without_thread_pool/BasePartition.h"
#include "../include/partition_threads/with_thread_pool/thread_pool_impl/BasePartitionThreadPool.h"
#include "../include/found_primes/FoundPrimes.h"
#include "../include/partition_threads/with_thread_pool/thread_pool_impl/RangePartitionThreadPool.h"


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
