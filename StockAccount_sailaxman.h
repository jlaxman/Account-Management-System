
//class StockAccount handles stock portfolio by using doubly linked list
#ifndef STOCKACCOUNT_SAILAXMAN_H
#define	STOCKACCOUNT_SAILAXMAN_H

#include "Account_sailaxman.h"
#include "Node_sailaxman.h"
#include "Sort_sailaxman.h"
#include "BankAccount_sailaxman.h"

//Class StockAccount- to handle all the stock account related operations

class StockAccount : public Account{
public:
	StockAccount();
	~StockAccount();
	int size() const;
	void storePortfolio();
	void viewTransactionHistory();
	void plotGraph();
	void displayPortfolio();
	void updateStockPrices();
	void buyShares(string, int, double);
	void sellShares(string, int, double);
	double getStockPrice(const string&);
private:
    void saveTransaction(const string& type, const string& stockName, int numOfShares, double currAmtPerShare);
	Node *Head;
	int sz;	//stores the number of nodes in doubly linked list
	SortContext sortContext; // For implementing sort strategy design pattern
};

#endif