#include <cstdio>
#include <ostream>
#include <iostream>
#include <mutex>
#include <thread>
#include "../Customer.h"
#include <vector>
#include <string>
#include <chrono>
#include <future>
#define num_of_customer_transactions 10
#define NUM_OF_CUSTOMERS 5
using namespace std;
// mutex to syncronize printing
std::mutex printMutex;

// this function safely prints when no other thread is printing to output
void safeprint(string s){
 std::lock_guard<std::mutex> lock1(printMutex);
 cout<<s<<endl;
}

// this function transfer may cause deadlock because it does not implement lock ordering
void deadlock_transfer(Account& from, Account& to, double amount) {
    string s ="Attempting to transfer " + std::to_string(amount) +" from account "+ std::to_string(from.id) +" to account "+ std::to_string( to.id);
    safeprint(s);
    from.mutex.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate some work
    to.mutex.lock();

    if (amount <= from.balance) {
        from.balance -= amount;
        to.balance += amount;
        safeprint("Transfer success "+ std::to_string(from.id) + "\n");
    } else {
        safeprint("Transfer failed "+ std::to_string(from.id) + "\n");
    }

    to.mutex.unlock();
    from.mutex.unlock();
}
template <typename Callable, typename... Args>
bool runWithTimeout(Callable&& func, std::chrono::milliseconds timeout, Args&&... args) {
    std::future<void> result = std::async(std::launch::async, std::forward<Callable>(func), std::forward<Args>(args)...);

    if (result.wait_for(timeout) == std::future_status::timeout) {
        safeprint("Deadlock Detected. Resolving");
        return false; // Timeout occurred
    } else {
        safeprint("Function completed within timeout.");
        return true; // Function completed normally
    }
}
// this function transfer avoids deadlock by implementing lock ordering
void transfer(Account& from, Account& to, double amount) {
    string s ="Attempting to transfer " + std::to_string(amount) +" from account "+ std::to_string(from.id) +" to account "+ std::to_string( to.id);
    safeprint(s);
    if (from.id < to.id) {
        std::lock_guard<std::mutex> lock1(from.mutex);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate some work
        std::lock_guard<std::mutex> lock2(to.mutex);
    } else {
        std::lock_guard<std::mutex> lock1(to.mutex);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate some work
        std::lock_guard<std::mutex> lock2(from.mutex);
    }
    if (amount <= from.balance) {
        from.balance -= amount;
        to.balance += amount;
        safeprint("Transfer success "+ std::to_string(from.id) + "\n");
    } else {
        safeprint("Transfer failed "+ std::to_string(from.id) + "\n");
    }

    to.mutex.unlock();
    from.mutex.unlock();
}
// run the deadlock test with the unsafe function deadlock_transfer
void simulateDeadlock(Account& account1, Account& account2, Account& account3) {
    std::thread t1(deadlock_transfer, std::ref(account1), std::ref(account2), 1.0);
    std::thread t2(deadlock_transfer, std::ref(account2), std::ref(account3), 1.0);
    std::thread t3(deadlock_transfer, std::ref(account3), std::ref(account1), 1.0);

    t1.join();
    t2.join();
    t3.join();
}
void simulateDeadlockDetection(Account& account1, Account& account2, Account& account3) {
    std::thread t1([&]() { runWithTimeout(transfer, std::chrono::seconds(1), std::ref(account1), std::ref(account2), 50.00); });
    std::thread t2([&]() { runWithTimeout(transfer, std::chrono::seconds(1), std::ref(account2), std::ref(account3), 50.00); });
    std::thread t3([&]() { runWithTimeout(transfer, std::chrono::seconds(1), std::ref(account3), std::ref(account1), 50.00); });
    t1.join();
    t2.join();
    t3.join();
}
// run the deadlock simulation with the safe function transfer
void simulateDeadlockAvoidanace(Account& account1, Account& account2, Account& account3) {
    std::thread t1(transfer, std::ref(account1), std::ref(account2), 1.0);
    std::thread t2(transfer, std::ref(account2), std::ref(account3), 1.0);
    std::thread t3(transfer, std::ref(account3), std::ref(account1), 1.0);

    t1.join();
    t2.join();
    t3.join();
}

int main(){
    Customer allcustomers[NUM_OF_CUSTOMERS];
    vector<std::thread> threads;

    Account a;
    a.balance = 100;
    Account b;
    b.balance = 100;
    Account c;
    c.balance = 100;
    cout<<"Running transfers with deadlock protection ON:"<<endl<<endl;
    simulateDeadlockAvoidanace(a,b,c);
    simulateDeadlockDetection(a, b, c);

    cout<<"Press ENTER to run transfers without deadlock (This will likely crash the program): "<<endl;
    getchar();
    simulateDeadlock(a,b,c);
    for (int i=0;i<NUM_OF_CUSTOMERS;i++){
        cout<<"Account "<<allcustomers[i].account.id <<" final balance: $" << allcustomers[i].account.balance<<endl;
    }

    return 0;
}
