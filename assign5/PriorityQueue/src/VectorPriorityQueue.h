/**
  * VectorPriorityQueue
  * --------------------
  * This priority queue uses an unsorted Vector of PQEntries to store
  * its elements. The enqueue is very efficient, as new elements are 
  * appended onto the end of the vector. The dequeue, peek, and peekPriority
  * aren't very efficient, because the class needs to look through the entire
  * vector to find the smallest element. 
  */

#ifndef _vectorpriorityqueue_h
#define _vectorpriorityqueue_h

#include <iostream>
#include <string>
#include "vector.h"
#include "PQEntry.h"
using namespace std;

class VectorPriorityQueue {
public:
    /**
     * @brief VectorPriorityQueue
     * Constructor for vector priority queue. Takes no arguments, and no prior 
     * setup required, so empty.
     */
    VectorPriorityQueue();
    
    /**
     * @brief ~VectorPriorityQueue
     * Destructor for vector priority queue. No clean up required, so empty.
     */
    ~VectorPriorityQueue();
    
    /**
     * @brief changePriority
     * Changes the priority of one of the entries. Loops through the entire 
     * vector looking for the entry with the given value, then changes its 
     * priority if found. If an entry with the value is not found, or if the
     * entry's priority is already more urgent than the newPriority, then
     * the method will throw an exception and not change anything.
     * O(n) - worst case = entry isn't there, look through every element
     * @param value - Value of the entry the user wants to change.
     * @param newPriority - New priority that the desired entry should have.
     */
    void changePriority(string value, int newPriority);
    
    /**
     * @brief clear
     * Clears the priority queue. 
     * O(n) - clears each element in the queue.
     */
    void clear();
    
    /**
     * @brief dequeue
     * Dequeues the most urgent entry and returns its value.
     * O(n) - worst case = most urgent element is at the end of the queue.
     * @return - The value of the most urgent entry.
     */
    string dequeue();
    
    /**
     * @brief enqueue
     * Enqueues a given entry onto the end of the vector priority queue.
     * O(1) - always adds on to the end.
     * @param value - Value of the new entry.
     * @param priority - Priority of the new entry.
     */
    void enqueue(string value, int priority);
    
    /**
     * @brief isEmpty
     * Returns if the priority queue has no elements.
     * O(1) - checks private size variable.
     * @return - Whether priority queue has no elements.
     */
    bool isEmpty() const;
    
    /**
     * @brief peek
     * Returns the value of the most urgent entry without changing the
     * priority queue.
     * O(n) - worst case = most urgent element is at the end of the queue.
     * @return - Value of the most urgent entry.
     */
    string peek() const;
    
    /**
     * @brief peekPriority
     * Returns the priority of the most urgent entry without changing the
     * priority queue.
     * O(n) - worst case = most urgent element is at the end of the queue.
     * @return - Priority of the most urgent entry.
     */
    int peekPriority() const;
    
    /**
     * @brief size
     * Returns the number of elements in the priority queue.
     * O(1) - checks private size variable.
     * @return - Number of elements.
     */
    int size() const;
    
    /**
     * @brief operator <<
     * Formats printing of priority queue. Loops through the queue and prints
     * every element.
     * O(n) - goes through each element in the queue.
     * @param out - String represntation of queue to be printed.
     * @param queue - Priority queue to be printed.
     * @return 
     */
    friend ostream& operator <<(ostream& out, const VectorPriorityQueue& queue);

private:
    /**
     * @brief priorityQueue
     * Private variable that keeps track of vector of PQEntries.
     */
    Vector<PQEntry> priorityQueue;
    
    /**
     * @brief getMostUrgentElement
     * Loops through the entire queue and returns the most urgent element.
     * O(n) - always needs to look through the entire queue.
     * @return - The index of the most urgent element.
     */
    int getMostUrgentElement() const;
    
    /**
     * @brief getElemAtIndex
     * Returns element at the specified index.
     * @param index
     * @return - found PQEntry
     */
    PQEntry getElemAtIndex(int index) const;
};

#endif
