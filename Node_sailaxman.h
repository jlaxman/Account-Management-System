// Node.h
#ifndef NODE_SAILAXMAN_H
#define NODE_SAILAXMAN_H

#include <string>
using namespace std;

class Node {
    friend class StockAccount;
    friend class SortImplementation;
    friend class SortSelection;
    friend class SortBubble;
    friend class SortContext;

public:
    // Default constructor declaration
    Node(string name, int n, double pps);
	static void swap(Node* , Node* );

private:
    string stockName;
    int numOfShares;
	double pricePerShare; // this will randomly fetched and updated to mimic the stock movement
    Node *next;
    Node *prev;
};

#endif // NODE_SAILAXMAN_H
