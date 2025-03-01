#include <ostream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <mutex>
#include <iomanip>
#include <random>

using namespace std;

// Structure to represent a bank account
struct Account {
public:
    double balance; // Stores account balance
    std::mutex mutex; // Mutex for thread-safe operations
    bool unsafe_mutex; // Flag for unsafe operations
    int id; // Unique account ID
    
    // Constructor to initialize account with default balance and random ID
    Account() {
        balance = 100; // Initial balance set to 100
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 1000);
        id = distrib(gen); // Assign a random ID
    }

    // Withdraw function with thread safety
    void withdrawl(double amount) {
        lock_account(); // Lock the account before modification
        if (amount <= balance) {
            balance -= amount;
            std::cout << std::setw(10) << "Withdrew" << std::setw(10) << amount
                      << " from account " << std::setw(4) << id
                      << ". New balance: " << std::fixed << std::setprecision(2) << balance << std::endl;
        } else {
            std::cout << std::setw(10) << "Withdrawl failed. Insufficient funds in account " << id << std::endl;
        }
    }

    // Deposit function with thread safety
    void deposit(double amount) {
        lock_account(); // Lock the account before modification
        balance += amount;
        std::cout << std::setw(10) << "Deposited" << std::setw(10) << amount
                  << " to account " << std::setw(4) << id
                  << ". New balance: " << std::fixed << std::setprecision(2) << balance << std::endl;
    }

    // Unsafe withdraw function (not using mutex)
    void unsafe_withdrawl(double amount) {
        unsafe_mutex = true; // Indicating an unsafe operation
        if (amount <= balance) {
            balance -= amount;
            std::cout << std::setw(10) << "Unsafe Withdrew" << std::setw(10) << amount
                      << " from account " << std::setw(4) << id
                      << ". New balance: " << std::fixed << std::setprecision(2) << balance << std::endl;
        }
    }

    // Unsafe deposit function (not using mutex)
    void unsafe_deposit(double amount) {
        unsafe_mutex = true; // Indicating an unsafe operation
        balance += amount;
        std::cout << std::setw(10) << "Unsafe Deposited" << std::setw(10) << amount
                  << " to account " << std::setw(4) << id
                  << ". New balance: " << std::fixed << std::setprecision(2) << balance << std::endl;
    }

private:
    // Helper function to lock the account using a mutex
    void lock_account() {
        std::lock_guard<std::mutex> lock(mutex); // Ensures thread safety
    }
};
