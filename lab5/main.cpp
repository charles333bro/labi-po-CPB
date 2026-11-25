#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <windows.h>

using namespace std;

class MyMutex {
private:
    atomic<bool> locked;

public:
    MyMutex() {
        locked = false;
    }

    void lock() {
        bool expected = false;
        while (!locked.compare_exchange_weak(expected, true)) {
            expected = false;
            this_thread::yield();
        }
    }

    void unlock() {
        locked = false;
    }
};

int dish1 = 3000;
int dish2 = 3000;
int dish3 = 3000;

int eaten1 = 0;
int eaten2 = 0;
int eaten3 = 0;

bool cook_fired = false;
bool all_exploded = false;
bool time_up = false;

MyMutex m;

int gluttony = 1;
int efficiency = 1;

void fat_man(int id, int& dish, int& eaten) {
    while (true) {
        m.lock();
        if (cook_fired || all_exploded || time_up) {
            m.unlock();
            break;
        }

        if (eaten >= 10000) {
            m.unlock();
            this_thread::sleep_for(chrono::milliseconds(1));
            continue;
        }

        if (dish > 0) {
            if (dish >= gluttony) {
                dish -= gluttony;
                eaten += gluttony;
            } else {
                eaten += dish;
                dish = 0;
            }
        } else {
            cook_fired = true; 
        }

        m.unlock();
        this_thread::sleep_for(chrono::milliseconds(1)); 
    }
}

void cook() {
    while (true) {
        m.lock();
        if (cook_fired || all_exploded || time_up) {
            m.unlock();
            break;
        }
        
        dish1 += efficiency;
        dish2 += efficiency;
        dish3 += efficiency;
        
        m.unlock();
        this_thread::sleep_for(chrono::milliseconds(2)); 
    }
}

void timer() {
    this_thread::sleep_for(chrono::seconds(5));
    time_up = true;
}

void check_explosion() {
    while (true) {
        m.lock();
        if (cook_fired || all_exploded || time_up) {
            m.unlock();
            break;
        }
        if (eaten1 >= 10000 && eaten2 >= 10000 && eaten3 >= 10000) {
            all_exploded = true;
        }
        m.unlock();
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

void run_simulation(int g, int e, string scenario_name) {
    dish1 = 3000; dish2 = 3000; dish3 = 3000;
    eaten1 = 0; eaten2 = 0; eaten3 = 0;
    cook_fired = false; all_exploded = false; time_up = false;
    
    gluttony = g;
    efficiency = e;

    cout << "Сценарий: " << scenario_name << endl;
    cout << "gluttony = " << g << ", efficiency = " << e << endl;

    thread t1(fat_man, 1, ref(dish1), ref(eaten1));
    thread t2(fat_man, 2, ref(dish2), ref(eaten2));
    thread t3(fat_man, 3, ref(dish3), ref(eaten3));
    thread t_cook(cook);
    thread t_time(timer);
    thread t_check(check_explosion);

    t1.join();
    t2.join();
    t3.join();
    t_cook.join();
    t_time.join();
    t_check.join();

    if (cook_fired) {
        cout << "РЕЗУЛЬТАТ: кука уволили (Наггетсы закончились)" << endl;
    } else if (all_exploded) {
        cout << "РЕЗУЛЬТАТ: кук не получил зарплату (Все толстяки лопнули)" << endl;
    } else if (time_up) {
        cout << "РЕЗУЛЬТАТ: кук уволился сам (Прошло 5 дней)" << endl;
    }
    cout << "Съедено: " << eaten1 << ", " << eaten2 << ", " << eaten3 << "\n" << endl;
}

int main() {
    SetConsoleOutputCP(65001);

    run_simulation(100, 1, "кука уволили");
    run_simulation(100, 200, "кук не получил зарплату");
    run_simulation(1, 1, "кук уволился сам");

    system("pause");
    return 0;
}