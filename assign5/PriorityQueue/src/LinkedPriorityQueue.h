/**
  * LinkedPriorityQueue
  * --------------------
  * This priority queue uses a sorted linked list of ListNodes to store 
  * its elements. The enqueue is not very efficient, as new elements must
  * be inserted in sorted order. The dequeue, peek, and peekPriority are
  * very efficient because the most urgent element is always at the beginning
  * of the queue.
  */

#ifndef _linkedpriorityqueue_h
#define _linkedpriorityqueue_h

#include <cstddef>    // for NULL
#include <iostream>
#include <string>
#include "ListNode.h"
#include "PQEntry.h"
#include "error.h"
using namespace std;

/*
 * For documentation of each member, see VectorPriorityQueue.h.
 */
class LinkedPriorityQueue {
public:
    /**
     * @brief LinkedPriorityQueue
     * Constructor - sets pointer to head of linked list to null. 
     */
    LinkedPriorityQueue();
    
    /**
     * @brief ~LinkedPriorityQueue
     * Destructor - uses clear() function to clear linked list. 
     */
    ~LinkedPriorityQueue();
    
    // See VectorPriorityQueue.h for documentation member functions.
    
    /**
     * @brief changePriority
     * O(n) - worst case = entry to cchange isn't in the linked list.
     * @param value
     * @param newPriority
     */
    void changePriority(string value, int newPriority);
    
    /**
     * @brief clear
     * O(n) - loops through each element in the linked list.
     */
    void clear();
    
    /**
     * @brief dequeue
     * O(1) - always the first element
     * @return 
     */
    string dequeue();
    
    /**
     * @brief enqueue
     * O(n) - worst case = enqueueing least urgent entry, so have to put it 
     * at the end of the linked list
     * @param value
     * @param priority
     */
    void enqueue(string value, int priority);
    
    /**
     * @brief isEmpty
     * O(1) - check if head is NULL
     * @return 
     */
    bool isEmpty() const;
    
    /**
     * @brief peek
     * O(1) - always first element
     * @return 
     */
    string peek() const;
    
    /**
     * @brief peekPriority
     * O(1) - always first element
     * @return 
     */
    int peekPriority() const;
    
    /**
     * @brief size
     * O(n) - loops through linked list and counts number of elements
     * @return 
     */
    int size() const;
    
    /**
     * @brief operator <<
     * O(n) - loops through linked list and prints out each element
     * @param out
     * @param queue
     * @return 
     */
    friend ostream& operator <<(ostream& out, const LinkedPriorityQueue& queue);

private:
    /**
     * @brief head
     * Pointer to first element in linked list.
     */
    ListNode *head;
};

#endif
