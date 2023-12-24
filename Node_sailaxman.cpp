// Node.cpp
#include "Node_sailaxman.h"

// Constructor implementation
Node::Node(string name, int n, double pps)
    : stockName(name), numOfShares(n), pricePerShare(pps), next(NULL), prev(NULL) {
   
}
void Node::swap(Node *a, Node *b) {
    string tempStockName = a->stockName;
    int tempNumOfShares = a->numOfShares;
    double tempPricePerShare = a->pricePerShare;

    a->stockName = b->stockName;
    a->numOfShares = b->numOfShares;
    a->pricePerShare = b->pricePerShare;

    b->stockName = tempStockName;
    b->numOfShares = tempNumOfShares;
    b->pricePerShare = tempPricePerShare;
}


