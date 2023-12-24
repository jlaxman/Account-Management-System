#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <unordered_map>
#include <vector>


using namespace std;


#include "StockAccount_sailaxman.h"
#include "BankAccount_sailaxman.h"
#include "Node_sailaxman.h"

//default constructor
StockAccount::StockAccount() : Head(nullptr) {
    sz = 0;
    sortContext.setSortStrategy(new SortSelection());

    // Reading stock transaction history
    ifstream stockFile("stock_transaction_history.txt");
    unordered_map<string, int> stockCounts;

    if (stockFile.is_open()) {
        string transactionType, stockSymbol, sharesStr, pricePerShare, totalPrice, transactionTime, line;
        while (getline(stockFile, line)) {
            stringstream lineStream(line);
            if (!(lineStream >> transactionType >> stockSymbol >> sharesStr >> pricePerShare >> totalPrice >> transactionTime)) {
                cout << "Error reading file! Stock Transaction" << endl;
                break; // Error handling
            }

            int shares = stoi(sharesStr);
            if (transactionType == "Buy") {
                stockCounts[stockSymbol] += shares;
            } else if (transactionType == "Sell") {
                stockCounts[stockSymbol] -= shares;
            }
        }
    }
    stockFile.close();

    // Building the doubly linked list (DLL) from the stock counts
    Node* currentNode = nullptr;
    for (const auto& [symbol, quantity] : stockCounts) {
        if (quantity > 0) {
            Node* newNode = new Node(symbol, quantity, getStockPrice(symbol));
            if (!Head) {
                Head = newNode;
                currentNode = Head;
            } else {
                currentNode->next = newNode;
                newNode->prev = currentNode;
                currentNode = newNode;
            }
            sz++;
        }
    }

    if (Head) {
       Head = sortContext.executeSort(Head);
     }

}

//function for randomly pick the price for a stock from 4 Result.txt files
double StockAccount::getStockPrice(const string& stockname) {
    string fileNames[4] = {"Result_1.txt", "Result_2.txt", "Result_3.txt", "Result_4.txt"};

    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand() % 4;  // Generate a random index between 0 and 3

    string selectedFileName = fileNames[randomIndex];
    string line;

    ifstream fileStream(selectedFileName);
    if (fileStream.is_open()) {
        for (string temp; fileStream >> temp; ) {
            if (temp == stockname) {
                fileStream >> temp;
                return stod(temp);  // Convert the string to double and return the stock price
            }
        }
        fileStream.close();
    } else {
        cout << "Error in opening file: " << selectedFileName << endl;
    }

    // If the stock symbol is not found, return -1
    return -1;
}

//function for displaying the current portfolio
void StockAccount::displayPortfolio() {
    double total = 0.0;

    // Check if the list is empty, indicating no stocks in the portfolio
    if (size() == 0) {
        cout << endl << "Cash balance= $" << getCashBalance() << endl << endl;
        cout << "The stock portfolio is empty" << endl;
        cout << "Total portfolio value= $" << getCashBalance() << endl;
        return;
    } else {
        cout << endl << "Cash balance= $" << getCashBalance() << endl << endl;
        cout << left << setw(18) << "Company Symbol" << left << setw(11) << "Number" << left << setw(19) << "Price per share" << "Total value" << endl;

        
        for (Node* currentNode = Head; currentNode != nullptr; currentNode = currentNode->next) {
            cout << setprecision(2) << fixed;
            currentNode->pricePerShare = getStockPrice(currentNode->stockName);
            cout << left << setw(18) << currentNode->stockName 
                 << left << setw(11) << currentNode->numOfShares 
                 << left << setw(1) << "$" << left << setw(18) << currentNode->pricePerShare 
                 << left << setw(1) << "$" << currentNode->numOfShares * currentNode->pricePerShare << endl;
            
            total += currentNode->numOfShares * currentNode->pricePerShare;
        }

        cout << "Total portfolio value= $" << getCashBalance() + total << endl;
    }
}

//function for updating the list according to most recent price per share 
void StockAccount::updateStockPrices() {
    // Iterate over the list and update the stock prices
    for (Node* currentNode = Head; currentNode != nullptr; currentNode = currentNode->next) {
        currentNode->pricePerShare = getStockPrice(currentNode->stockName);
    }
}

//function for buying shares
void StockAccount::buyShares(string stockName, int numOfShares, double maxAmtPerShare) {
    double currAmtPerShare;
    int choice;

    // Check if the purchase can be covered by the cash balance
    if (numOfShares * maxAmtPerShare > getCashBalance()) {
        cout << "Transaction failed due to insufficient cash balance in bank account" << endl << endl;
        return;
    }

    currAmtPerShare = getStockPrice(stockName);

    // Check if the stock symbol is valid
    if (currAmtPerShare == -1) {
        cout << "Symbol not found!!!" << endl << endl;
        return;
    }

    // Check if the current price per share exceeds the max amount willing to pay
    if (currAmtPerShare > maxAmtPerShare) {
        cout << "Transaction failed because price per share is higher than the maximum amount you are willing to pay" << endl << endl;
        return;
    }

    Node* newNode = new Node(stockName, numOfShares, currAmtPerShare);

    if (size() == 0) {
        Head = newNode;
        sz++;
    } else {
        bool isStockFound = false;
        for (Node* currentNode = Head; currentNode != nullptr; currentNode = currentNode->next) {
            if (currentNode->stockName == newNode->stockName) {
                currentNode->numOfShares += newNode->numOfShares;
                isStockFound = true;
                break;
            }
        }

        if (!isStockFound) {
            Node* lastNode = Head;
            for (; lastNode->next != nullptr; lastNode = lastNode->next);
            lastNode->next = newNode;
            newNode->prev = lastNode;
            sz++;
        }
    }

    double transactionAmount = numOfShares * currAmtPerShare;
	BankAccount* bankAccount = BankAccount::getInstance();
    bankAccount->withdraw(transactionAmount);
   

    cout << "You have purchased " << numOfShares << " shares of " << stockName << " at $" << currAmtPerShare << " each for a total of $" << transactionAmount << endl;

    saveTransaction("Buy", stockName, numOfShares, currAmtPerShare);

    updateStockPrices(); // Update stock prices for all stocks in the list

    // Implementing the Design Pattern: strategy for sorting
    if (size() > 1) {
        cout << endl << "Select the sorting algorithm that you would like to use" << endl;
        cout << "1: Selection sort" << endl;
        cout << "2: Bubble sort" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            // Set Selection sort strategy
            sortContext.setSortStrategy(new SortSelection());
            Head = sortContext.executeSort(Head);
            break;
        case 2:
            // Set Bubble sort strategy
            sortContext.setSortStrategy(new SortBubble());
            Head = sortContext.executeSort(Head);
            break;
        default:
            cout << "You have entered an incorrect choice" << endl;
            break;
        }
    }

    displayPortfolio();
}

//function for selling shares
void StockAccount::sellShares(string stockName, int numOfShares, double minAmtPerShare) {
    double currAmtPerShare = getStockPrice(stockName);
    Node *currentNode = Head;
    Node *tempNode = nullptr;
    int choice;
    bool isStockFound = false;

    if (size() == 0) {
        cout << "The stock portfolio is empty" << endl;
        return;
    }

    while (currentNode != nullptr) {
        if (currentNode->stockName == stockName) {
            isStockFound = true;

            if (numOfShares > currentNode->numOfShares) {
                cout << "Transaction failed due to insufficient number of shares" << endl;
                break;
            }

            if (currAmtPerShare < minAmtPerShare) {
                cout << "Transaction failed because the price per share is less than the minimum amount you are willing to sell" << endl;
                break;
            }

            currentNode->numOfShares -= numOfShares;

            // Check if the stock needs to be removed from the list
            if (currentNode->numOfShares == 0) {
                tempNode = currentNode;

                if (Head == currentNode) {
                    Head = currentNode->next;
                }

                if (currentNode->next != nullptr) {
                    currentNode->next->prev = currentNode->prev;
                }

                if (currentNode->prev != nullptr) {
                    currentNode->prev->next = currentNode->next;
                }

                sz--;
            }

            double transactionAmount = numOfShares * currAmtPerShare;
            BankAccount* bankAccount = BankAccount::getInstance();
            bankAccount->deposit(transactionAmount);

            cout << "You have sold " << numOfShares << " shares of " << stockName << " at $" << currAmtPerShare << " each for a total of $" << transactionAmount << endl;

            // Logging the transaction
			saveTransaction("Sell", stockName, numOfShares, currAmtPerShare);


            break;
        }

        currentNode = currentNode->next;
    }

    if (!isStockFound) {
        cout << "Symbol not found!!!" << endl;
    }

    updateStockPrices(); // Update stock prices for all stocks in the list to mimic stock movement

    // Implementing the Design Pattern: strategy for sorting using SortContext
    if (size() > 1 && isStockFound) {
        cout << endl << "Select the sorting algorithm that you would like to use" << endl;
        cout << "1: Selection sort" << endl;
        cout << "2: Bubble sort" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            sortContext.setSortStrategy(new SortSelection());
            break;
        case 2:
            sortContext.setSortStrategy(new SortBubble());
            break;
        default:
            cout << "Invalid choice. Defaulting to Selection Sort." << endl;
            sortContext.setSortStrategy(new SortSelection());
            break;
        }

        Head = sortContext.executeSort(Head);
    }

    displayPortfolio();

    
    delete tempNode;
}

//function for storing the portfolio, total portfolio value
void StockAccount::storePortfolio() {
    double totalPortfolioValue = 0.0;

    // Iterate over the list to calculate the total portfolio value
    for (Node* currentNode = Head; currentNode != nullptr; currentNode = currentNode->next) {
        currentNode->pricePerShare = getStockPrice(currentNode->stockName);
        totalPortfolioValue += currentNode->numOfShares * currentNode->pricePerShare;
    }

    // Store the total portfolio value in a file
    ofstream file2;
    file2.open("portfolio_history.txt", ios::app);
    time_t seconds;
    seconds = time(NULL);
    char date[9];
    tm *timeinfo;
    timeinfo = localtime(&seconds);
    strftime(date, 100, "%D", timeinfo);
    file2 << setprecision(2) << fixed;
    double bal=getCashBalance();
    file2 << left << setw(16) << bal << left << setw(16) << bal + totalPortfolioValue << left << setw(16) << seconds << left << setw(16) << date << endl;
    file2.close();
}

//function for plotting graph in Rplots.pdf using R
void StockAccount::plotGraph() {
    system("Rscript plotPortfolioGraphs.R");
}

//function for viewing the transaction history
void StockAccount::viewTransactionHistory() {
    string line;
    ifstream transactionFile("stock_transaction_history.txt");

    // Display the header for transaction history
    cout << left << setw(10) << "Event" 
         << left << setw(16) << "Company Symbol" 
         << left << setw(8) << "Number" 
         << left << setw(20) << "Price per share" 
         << left << setw(16) << "Total value" 
         << "Time" << endl;

    if (transactionFile.is_open()) {
        // Read and display each line from the transaction history file
        while (getline(transactionFile, line)) {
            cout << line << endl;
        }
        transactionFile.close();
    } else {
        cout << "Error in opening file" << endl;
    }
}

//function to count of DLL nodes
int StockAccount::size() const{return sz;}

//destructor
StockAccount::~StockAccount() {
    // Store the current portfolio state before destruction
    storePortfolio();

    // Delete all nodes in the list using a for loop
    for (Node* currentNode = Head; currentNode != nullptr; ) {
        Node* nextNode = currentNode->next;  // Store the next node
        delete currentNode;                  // Free the current node
        currentNode = nextNode;              // Move to the next node
    }
    
}


void StockAccount::saveTransaction(const string& type, const string& stockName, int numOfShares, double currAmtPerShare) {
        ofstream file2;
        file2.open("stock_transaction_history.txt", ios::app);

        double transactionAmount = numOfShares * currAmtPerShare;
		time_t seconds;
        seconds = time(NULL);
        char timeStr[9];
        tm *timeinfo = localtime(&seconds);
        strftime(timeStr, sizeof(timeStr), "%X", timeinfo);
        string time=string(timeStr);

        file2 << setprecision(2) << fixed;
        file2 << left << setw(10) << type << left << setw(16) << stockName
              << left << setw(8) << numOfShares << left << left << setw(1) << "$"
              << setw(19) << currAmtPerShare << left << setw(1) << "$"
              << left << setw(15) << transactionAmount << time << endl;

        file2.close();
    }


