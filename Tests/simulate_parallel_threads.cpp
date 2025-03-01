#include <ostream>
#include <iostream>
#include <mutex>
#include <thread>
#include "../Customer.h"
#include <vector>
#define NUM_OF_CUSTOMERS 100
using namespace std;

int main(){
    Customer allcustomers[NUM_OF_CUSTOMERS];
    vector<std::thread> threads;
    for(int i=0;i<NUM_OF_CUSTOMERS;i++){
        threads.emplace_back([&allcustomers, i]() {
            allcustomers[i].start();
        });
    }
    for (auto& thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }

    return 0;
}
