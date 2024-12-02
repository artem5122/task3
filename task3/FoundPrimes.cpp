#pragma once
#include "FoundPrimes.h"
#include <iostream>
#include <fstream>

FoundPrimes::FoundPrimes(const std::vector<int>& basicNumbers, const std::vector<int>& primeNumbers) {
    finalPrimeNumbers = basicNumbers; 
    finalPrimeNumbers.insert(finalPrimeNumbers.end(), primeNumbers.begin(), primeNumbers.end());
}

void FoundPrimes::printToConsole(){
    for (const auto& prime : finalPrimeNumbers) {
        std::cout << prime << std::endl;
    }
}

void FoundPrimes::printToFile(const std::string& filename){
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& prime : finalPrimeNumbers) {
            file << prime << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Ошибка открытия файла" << std::endl;
    }
}
