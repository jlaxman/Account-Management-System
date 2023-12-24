#include "BankAccount_sailaxman.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Initialize the static instance pointer
BankAccount* BankAccount::instance = nullptr;

// Static method to get the instance of the class
BankAccount* BankAccount::getInstance() {
    if (instance == nullptr) {
        instance = new BankAccount();
    }
    return instance;
}

// Private Constructor
BankAccount::BankAccount() {
    loadAccountBalance();
}

// Destructor
BankAccount::~BankAccount() {
    // Destructor code (if any)
}

// Implement deposit function
void BankAccount::deposit(double amount) {
    if (amount > 0) {
        setCashBalance(getCashBalance() + amount);
        addTransaction("Deposit", amount);
    } else {
        cerr << "Invalid deposit amount." << endl;
    }
}

// Implement withdraw function
void BankAccount::withdraw(double amount) {
    if (amount > 0 && amount <= getCashBalance()) {
        setCashBalance(getCashBalance() - amount);
        addTransaction("Withdrawal", amount);
    } else {
        cerr << "Invalid withdrawal amount or insufficient funds." << endl;
    }
}

// View account balance
void BankAccount::viewAccountBalance() const {
    cout << "Account balance: $" << getCashBalance() << endl;
}

// Print transaction history
void BankAccount::printHistory() const {
    ifstream file("bank_transaction_history.txt");
    if (file.is_open()) {
        cout << left << setw(13) << "Event" << left << setw(14) << "Amount" << left << setw(8) << "Date" << left << setw(20) << "Balance" << endl;
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "No transaction history found." << endl;
    }
}

// Load account balance from file
void BankAccount::loadAccountBalance() {
    ifstream file("portfolio_history.txt");
    if (file.is_open()) {
        string line;
        double lastBalance = 10000.0; // Default balance

        // Read through the file line by line
        while (getline(file, line)) {
            istringstream iss(line);
            double balance;

            // Read only the first value from the line
            if (iss >> balance) {
                lastBalance = balance; // Update the last balance
            }
        }

        setCashBalance(lastBalance); // Set the balance to the last read value
        file.close();
    } else {
        // If the file does not exist, set the balance to the initial value of $10,000
        setCashBalance(10000.0);
    }
}

// Add a transaction to the history
void BankAccount::addTransaction(const string& type, double amount) {
    ofstream file("bank_transaction_history.txt", ios::app);
    if (!file.is_open()) {
        file.open("bank_transaction_history.txt", ios::out);
    }
    
    time_t seconds;
    seconds = time(NULL);
    char date[9];
    tm *timeinfo;
    timeinfo = localtime(&seconds);
    strftime(date, 100, "%D", timeinfo);
    file << setprecision(2) << fixed;
    file << left << setw(13) << type << left << setw(1) << "$" << setw(11) << amount << left << setw(10) << date << left << setw(1) << "$" << left << setw(19) << getCashBalance() << endl;
    file.close();
}

// Get current date and time as string
string BankAccount::getCurrentDateTime() const {
    time_t now = time(nullptr);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}
