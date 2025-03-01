#include <ostream>
#include <iostream>
#include <mutex>
#include "Account.h"
#include <vector>

using namespace std;

#define num_of_customer_transactions 10 // Number of transactions each customer performs

// Class representing a Customer who owns an Account
class Customer {
private:
    int id; // Unique customer ID

public:
    Account account; // Each customer has an associated account

    // Constructor to initialize customer ID
    Customer() {
        static int nextId = 1; // Static variable to assign unique IDs
        id = nextId++;
    }

    // Function to simulate customer transactions
    void start() {
        for (int i = 0; i < num_of_customer_transactions; i++) {
            int x = rand(); // Generate a random number
            double y = double(x); // Convert to double (unused in logic)
            
            if (x % 2) { // If x is odd, deposit a random amount up to 50
                account.deposit(x % 50);
            } else { // If x is even, withdraw a fixed amount
                account.withdrawl(5.50);
            }
        }
    }
};
