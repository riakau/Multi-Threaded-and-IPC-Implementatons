#include <ostream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <mutex>
#include <random>
using namespace std;
struct Account{
    public:
    double balance;
    std::mutex mutex;
    bool unsafe_mutex;
    int id;
    Account(){
        balance =100;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 1000);
        id =  distrib(gen);
    }

    void withdrawl(double amount){
        lock_account();
        if (amount>= balance){
            balance -= amount;
        }
        else{
            cout<<"Withdrawl failed. Insufficient funds";
        }
        cout<<"Withdrew "<<amount<< " from account " << id<< ". New balance: "<< balance <<endl;
        
    }
    void deposit(double amount){
        lock_account();
        balance+=amount;
        cout<<"Deposited "<<amount<< " to account " << id<< ". New balance: "<< balance <<endl;

    }
    void unsafe_withdrawl(double amount){
        unsafe_mutex = true;
        if (amount>= balance){
            balance -= amount;
        }
        cout<<"Unsafe withdrawl of  "<<amount<< " from account " << id<< ". New balance: "<< balance <<endl;
    }
    void unsafe_deposit(double amount){
        unsafe_mutex = true;
        balance+=amount;
        cout<<"Unsafe deposit of  "<<amount<< " to account " << id<< ". New balance: "<< balance <<endl;
    }
    private:
    void lock_account(){
        std::lock_guard<std::mutex> lock(mutex);
    }
};
