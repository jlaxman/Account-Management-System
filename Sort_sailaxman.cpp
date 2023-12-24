#include "Sort_sailaxman.h"




// Implementation of SortSelection's sort method
Node* SortSelection::sort(Node *start) {
    Node *curr = start, *largest = start;

    while (largest) {
        curr = largest->next;

        while (curr) {
            if ((curr->numOfShares * curr->pricePerShare) > (largest->numOfShares * largest->pricePerShare)) {
                Node::swap(curr, largest);
            }
            curr = curr->next;
        }
        largest = largest->next;
    }
    return start;
}





// Implementation of SortBubble's sort method
Node* SortBubble::sort(Node *start) {
    bool swapped;
    Node *curr = nullptr;
    Node *lastPtr = nullptr;

    do {
        swapped = false;
        curr = start;

        while (curr->next != lastPtr) {
            if ((curr->numOfShares * curr->pricePerShare) < (curr->next->numOfShares * curr->next->pricePerShare)) {
                Node::swap(curr, curr->next);
                swapped = true;
            }
            curr = curr->next;
        }
        lastPtr = curr;
    } while (swapped);
    return start;
}

SortContext::SortContext() : strategy(nullptr) {}

SortContext::~SortContext() {
    delete strategy;
}

void SortContext::setSortStrategy(SortImplementation* newStrategy) {
    delete strategy;
    strategy = newStrategy;
}

Node* SortContext::executeSort(Node* Begin) {
    if (strategy != nullptr) {
        return strategy->sort(Begin);
    }
    // Return the original list if no strategy is set
    return Begin;
}
