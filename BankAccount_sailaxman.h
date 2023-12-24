#ifndef BANKACCOUNT_SAILAXMAN_H
#define BANKACCOUNT_SAILAXMAN_H

#include "Account_sailaxman.h"
#include <string>

// Singleton Design Pattern
// BankAccount class is designed as a singleton to ensure that only one instance
// of the class is created in the program.
class BankAccount : public Account {
public:
    // Static method to access the singleton instance.
    // This method ensures that only one instance of BankAccount exists.
    // It creates the instance if it doesn't exist and returns it.
    static BankAccount* getInstance();

    // Deleting the copy constructor and assignment operator
    // to prevent copying of the singleton instance.
    BankAccount(BankAccount const&) = delete;
    BankAccount& operator=(BankAccount const&) = delete;

    // Additional member functions
    void viewAccountBalance() const;
    void printHistory() const;
    void loadAccountBalance();
    void deposit(double amount);
    void withdraw(double amount);

private:
    // Private constructor to prevent instantiation outside the class.
    // The constructor will be called only once by getInstance().
    BankAccount();  
    virtual ~BankAccount();  // Destructor

    // Function to add a transaction record.
    void addTransaction(const std::string& type, double amount);

    // Utility function to get the current date and time as a string.
    std::string getCurrentDateTime() const;

    // Static member to hold the singleton instance.
    // This instance is managed internally by the class.
    static BankAccount* instance;
};

#endif // BANKACCOUNT_SAILAXMAN_H
