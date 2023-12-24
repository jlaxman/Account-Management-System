#ifndef SORT_SAILAXMAN_H
#define SORT_SAILAXMAN_H

#include <iostream>
#include <string>
#include "Node_sailaxman.h"

using namespace std;

// Strategy Interface
// SortImplementation is an interface for the Strategy pattern.
// It declares a common interface for all concrete sorting strategies.
// Classes implementing this interface will provide specific sorting algorithms.
class SortImplementation {
public:
    // Pure virtual function 'sort' that concrete strategies must implement.
    // This function takes the head of a linked list and returns the head of the sorted list.
    virtual Node* sort(Node *Begin) = 0;

    // Virtual destructor is essential for a class with virtual functions
    // to ensure derived class destructors are called correctly.
    virtual ~SortImplementation() {}
};

// Concrete Strategy 1: Selection Sort
// SortSelection implements the selection sort algorithm.
// It is a concrete class that inherits from SortImplementation and provides
// a specific strategy (selection sort) for sorting a linked list.
class SortSelection : public SortImplementation {
public:
    // Overriding the 'sort' function to apply the selection sort algorithm.
    // It rearranges the nodes of the list such that they are ordered based on the data they hold.
    virtual Node* sort(Node *Begin);

    // Destructor.
    virtual ~SortSelection() {}
};

// Concrete Strategy 2: Bubble Sort
// SortBubble implements the bubble sort algorithm.
// This class provides the bubble sort strategy for sorting,
// adhering to the SortImplementation interface.
class SortBubble : public SortImplementation {
public:
    // Overriding the 'sort' function to apply the bubble sort algorithm.
    // This method iteratively steps through the list, compares adjacent elements, and swaps them if they are in the wrong order.
    virtual Node* sort(Node *Begin);

    // Destructor.
    virtual ~SortBubble() {}
};

// Context Class
// SortContext is used to configure the desired sorting strategy at runtime.
// It acts as the context in the Strategy pattern, holding a reference
// to a SortImplementation strategy and delegating the sorting task to it.
class SortContext {
private:
    // Pointer to a strategy object that implements SortImplementation.
    // This strategy will be used to execute the sorting algorithm.
    SortImplementation* strategy;

public:
    // Constructor: Initializes the context without a specific strategy.
    SortContext();

    // Destructor: Ensures proper cleanup of the strategy object to avoid memory leaks.
    ~SortContext();

    // setSortStrategy allows changing the sorting strategy at runtime.
    // It accepts a pointer to a new SortImplementation strategy.
    void setSortStrategy(SortImplementation* newStrategy);

    // executeSort delegates the sorting task to the current strategy.
    // It takes the head of the linked list and returns the head of the sorted list.
    Node* executeSort(Node* Begin);
};

#endif // SORT_SAILAXMAN_H
