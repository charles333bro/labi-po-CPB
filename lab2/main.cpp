#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <time.h>

using namespace std;

mutex m;

void f1(string name) {
    long double kolm = 0;
    long double arthur = 0.000000001L;
    
    clock_t start = clock();
    double seconds = 0;
    
    while (seconds < 1.0) {
        kolm = kolm + arthur;
        
        clock_t end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
    }
    
    m.lock();
    cout << name << ": " << kolm << endl;
    m.unlock();
}

int main() {
    thread thread1(f1, "t1");
    thread thread2(f1, "t2");
    thread thread3(f1, "t3");

    thread1.join();
    thread2.join();
    thread3.join();

    system("pause");
    return 0;
}