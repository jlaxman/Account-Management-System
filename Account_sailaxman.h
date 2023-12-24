#ifndef ACCOUNT_SAILAXMAN_H
#define ACCOUNT_SAILAXMAN_H

#include <string>

class Account {
private:
    static double cashBalance;

public:
    Account(); // Constructor
    virtual ~Account() = 0; // Pure virtual destructor

    // Getter and setter for cashBalance
    double getCashBalance() const;
    void setCashBalance(double balance);
};

#endif //ACCOUNT_SAILAXMAN_H