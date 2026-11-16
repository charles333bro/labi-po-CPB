#include <iostream>
#include <thread>
#include <mutex>
#include <string>

using namespace std;

int coins = 101;
int Bob_coins = 0;
int Tom_coins = 0;
mutex m;

void coin_sharing(string name, int& my_coins, int& other_coins) {
    while (true) {
        m.lock();
        
        if (coins <= 0) {
            m.unlock();
            break;
        }
        
        if (coins == 1 && my_coins == other_coins) {
            m.unlock();
            break;
        }
        

        if (my_coins <= other_coins) {
            coins = coins - 1;
            my_coins = my_coins + 1;
            cout << name << " :" << my_coins << " " << other_coins << endl;
        }
        
        m.unlock();
    }
}

int main() {
    cout << "Start coins: " << coins << endl;

    thread thread1(coin_sharing, "Bob", ref(Bob_coins), ref(Tom_coins));
    thread thread2(coin_sharing, "Tom", ref(Tom_coins), ref(Bob_coins));

    thread1.join();
    thread2.join();

    cout << "\n--- Result ---" << endl;
    cout << "Bob: " << Bob_coins << endl;
    cout << "Tom: " << Tom_coins << endl;
    cout << "Dead man: " << coins << endl; 
    cout << "Total: " << Bob_coins + Tom_coins + coins << endl;

    system("pause");
    return 0;
}