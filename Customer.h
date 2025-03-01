#include <ostream>
#include <iostream>
#include <mutex>
#include "Account.h"
#include <vector>
using namespace std;
#define num_of_customer_transactions 10

class Customer{
    private:
        int id;
    public:
        Account account;
    Customer(){
    }
    void start(){
        for (int i=0; i < num_of_customer_transactions; i++){
            int x = rand();
            double y = double(x);
            if(x%2){
            account.deposit(x%50);
        } 
        else{ account.withdrawl(5.50);}
    
    }
    }
    };
