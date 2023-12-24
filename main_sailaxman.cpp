#include <iostream>
#include <string>
#include <iomanip>

#include "StockAccount_sailaxman.h"
#include "BankAccount_sailaxman.h"

using namespace std;

// Function prototypes
void displayMainMenu();
void handleStockAccount(Account* stockAcc);
void handleBankAccount();
void displayStockMenu();
void displayBankMenu();


int main() {
	
    vector<Account*> accounts;
    accounts.push_back(BankAccount::getInstance()); //
    accounts.push_back(new StockAccount());
    
    cout << "WELCOME TO THE ACCOUNT MANAGEMENT SYSTEM." << endl << endl;

    int mainMenuChoice = 0;

    while (mainMenuChoice != 3) {
        displayMainMenu();
        cin >> mainMenuChoice;

        switch (mainMenuChoice) {
            case 1:
                handleStockAccount(accounts[1]);
                break;
            case 2:
                handleBankAccount();
                break;
            case 3:
                cout << endl << "Thank you! Looking forward to seeing you again." << endl;
                break;
            default:
                cout << endl << "Invalid choice, please try again." << endl << endl;
                break;
        }
    }
    for(auto account: accounts){
        if (dynamic_cast<StockAccount*>(account)){
           delete account; // only stock account deleted, as singleton instance of Bank Account is automatically deleted
        }
    }
    return 0;
}

void displayMainMenu() {
    cout << "Please select an account to access:" << endl;
    cout << "1. Stock Portfolio Account " << endl;
    cout << "2. Bank Account" << endl;
    cout << "3. Exit " << endl;
    cout << endl << "Option: ";
}

void handleStockAccount(Account* stockAcc) {
    BankAccount* bankAccount = BankAccount::getInstance();
    StockAccount* stockAccount = dynamic_cast<StockAccount*>(stockAcc);
    int stockMenuChoice = 0;
    string stockSymbol;
    double price, maxPrice, minPrice;
    int numOfShares;

    while (stockMenuChoice != 7) {
        displayStockMenu();
        cin >> stockMenuChoice;

        switch (stockMenuChoice) {
            case 1:
                cout << endl << "Please enter the stock symbol: ";
                cin >> stockSymbol;
                price = stockAccount->getStockPrice(stockSymbol);
                if (price != -1) {
                    cout << "Company Symbol     " << "Price per share" << endl;
                    cout << stockSymbol << setw(18) << "$" << price << '\n';
                } else {
                    cout << "Symbol not found!!!" << endl;
                }
                break;
            case 2:
                stockAccount->displayPortfolio();
                break;
            case 3:
                cout << endl << "Please enter the stock symbol you want to purchase: ";
                cin >> stockSymbol;
                cout << "Please enter the number of shares: ";
                cin >> numOfShares;
                cout << "Please enter the maximum amount you are willing to pay per share: ";
                cin >> maxPrice;
                stockAccount->buyShares(stockSymbol, numOfShares, maxPrice);
                break;
            case 4:
                cout << endl << "Please enter the stock symbol you want to sell: ";
                cin >> stockSymbol;
                cout << "Please enter the number of shares: ";
                cin >> numOfShares;
                cout << "Please enter the minimum amount you are willing to sell per share: ";
                cin >> minPrice;
                stockAccount->sellShares(stockSymbol, numOfShares, minPrice);
                break;
            case 5:
                stockAccount->plotGraph();
                break;
            case 6:
                stockAccount->viewTransactionHistory();
                break;
            case 7:
                cout << endl << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl << endl;
                break;
        }
    }
}

void displayStockMenu() {
    cout << endl;
    cout << "Stock Portfolio Account" << endl;
    cout << "Please select an option:" << endl;
    cout << "1. Display the price for a stock symbol " << endl;
    cout << "2. Display the current portfolio" << endl;
    cout << "3. Buy shares" << endl;
    cout << "4. Sell shares" << endl;
    cout << "5. View a graph for the portfolio value" << endl;
    cout << "6. View transaction history" << endl;
    cout << "7. Return to previous menu " << endl;
    cout << endl << "Option: ";
}

void handleBankAccount() {
     BankAccount* bankAccount = BankAccount::getInstance();
    int bankMenuChoice = 0;
    double amount;

    while (bankMenuChoice != 5) {
        displayBankMenu();
        cin >> bankMenuChoice;

        switch (bankMenuChoice) {
            case 1:
                cout << "You have $" << bankAccount->getCashBalance() << " in your bank account" << endl;
                break;
            case 2:
                cout << "Please select the amount you wish to deposit: $";
                cin >> amount;
                bankAccount->deposit(amount);
                break;
            case 3:
                cout << "Please select the amount you wish to withdraw: $";
                cin >> amount;
                bankAccount->withdraw(amount);
                break;
            case 4:
                bankAccount->printHistory();
                break;
            case 5:
                cout << endl << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl << endl;
                break;
        }
    }
}

void displayBankMenu() {
    cout << endl;
    cout << "Bank Account" << endl;
    cout << "Please select an option:" << endl;
    cout << "1: View account balance " << endl;
    cout << "2: Deposit money" << endl;
    cout << "3: Withdraw money" << endl;
    cout << "4: Print out history" << endl;
    cout << "5: Return to previous menu " << endl;
    cout << endl << "Option: ";
}
