#include <iostream>
#include <string>
#include <time.h>
#include <thread>
#include <chrono>

using namespace std;

unsigned long long calculateFactorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}


void Func(string name) {
    volatile unsigned long long res = 0;
    for (int i = 0; i < 10000000; ++i) {
        res = calculateFactorial(10);
    }
    cout << name << " done" << endl;
}

int main() {
    cout << "pynkt 1.1" << endl;
    string s = "01234";
    
    //этот цикл вызывает ошибку. 
    
    //for (unsigned int i = s.size() - 1; i >= 0; i--) {
    //    cout << s[i] << endl;
    //}
    
    
    //исправленный вариант
    for (int i = s.size() - 1; i >= 0; i--) {
        cout << s[i] << endl;
    }

    //пункт 1.2
    cout << "\npynkt 1.2" << endl;
    const int iterations = 10000000;
    volatile unsigned long long final_result = 0;

    clock_t start = clock();
    for (int i = 0; i < iterations; ++i) {
        final_result = calculateFactorial(10);
    }
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "rezultat 10! = " << final_result << endl;
    cout << "time: " << seconds << " sec." << endl;

    //пункт 1.3
    cout << "\npynkt 1.3" << endl;
    
    auto start_seq = chrono::steady_clock::now();
    Func("t1");
    Func("t2");
    auto end_seq = chrono::steady_clock::now();
    chrono::duration<double> sec_seq = end_seq - start_seq;
    cout << "Posledovatelno: " << sec_seq.count() << " sec." << endl;

    auto start_par = chrono::steady_clock::now();
    thread thread1(Func, "t1");
    thread thread2(Func, "t2");
    thread1.join();
    thread2.join();
    auto end_par = chrono::steady_clock::now();
    chrono::duration<double> sec_par = end_par - start_par;
    cout << "V potokah: " << sec_par.count() << " sec." << endl;

    system("pause");
    return 0;
}