#include "Account_sailaxman.h"
double Account::cashBalance = 10000;
// Constructor
Account::Account(){
   
}

// Pure virtual destructor
Account::~Account() {}

// Getter for cashBalance
double Account::getCashBalance() const {
    return cashBalance;
}

// Setter for cashBalance
void Account::setCashBalance(double balance) {
    cashBalance = balance;
}