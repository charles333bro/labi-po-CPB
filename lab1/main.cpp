#include <iostream>
#include <string>
#include <time.h>


unsigned long long calculateFactorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int main() {
//Пункт 1.1 Разминка
    std::cout << "--- pynkt 1.1 ---" << std::endl;
    std::string s = "01234";
    std::cout << "Size: " << s.size() << std::endl; 
    
    for (unsigned int i = s.size() - 1; i >= 0; i--) {
        std::cout << s[i] << std::endl;
        if (i == 0) break; 
    }

    std::cout << "\n--- pynkt 1.2 ---" << std::endl;
    // Пункт 1.2 Упражнение 1
    const int iterations = 10000000; // 10 млн раз
    

    volatile unsigned long long final_result = 0;

    clock_t start = clock();
    
    for (int i = 0; i < iterations; ++i) {
        final_result = calculateFactorial(10);
    }
    
    clock_t end = clock();
    
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    
    std::cout << "rezultat 10! = " << final_result << std::endl;
    std::cout << "time: " << seconds << " sec." << std::endl;

    return 0;
}