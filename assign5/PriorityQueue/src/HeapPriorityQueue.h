/**
  * HeapPriorityQueue
  * --------------------
  * This priority queue uses a binary heap of PQEntries to store its elements.
  * The elements maintain heap ordering - each parent index is more urgent
  * than its two child indexes. The enqueue and dequeue are both fairly efficient -
  * at most they have to go down log(n) levels of the binary heap to rearrange 
  * the heap and maintain heap ordering. The peek and peekPriority are very efficient
  * because th emost urgent element is always at teh beginning of the queue.
  */

#ifndef _heappriorityqueue_h
#define _heappriorityqueue_h

#include <iostream>
#include <string>
#include "PQEntry.h"
#include "error.h"
using namespace std;

/*
 * For documentation of each member, see VectorPriorityQueue.h.
 */
class HeapPriorityQueue {
public:
    /**
     * @brief HeapPriorityQueue
     * Constructor - Initializes private size variables and creates new array.
     */
    HeapPriorityQueue();
    
    /**
     * @brief !HeapPriorityQueue
     * Destructor - Frees up array space.
     */
    ~HeapPriorityQueue();
    
    /**
     * @brief changePriority
     * O(log(n)) - has to check at most log(n) levels if entry isn't in the heap
     * @param value
     * @param newPriority
     */
    void changePriority(string value, int newPriority);
    
    /**
     * @brief clear
     * O(1) - deletes old array and creates a new one
     */
    void clear();
    
    /**
     * @brief dequeue
     * O(log(n))
     * @return 
     */
    string dequeue();
    
    /**
     * @brief enqueue
     * O(log(n))
     * @param value
     * @param priority
     */
    void enqueue(string value, int priority);
    
    /**
     * @brief isEmpty
     * O(1)
     * @return 
     */
    bool isEmpty() const;
    
    /**
     * @brief peek
     * O(1)
     * @return 
     */
    string peek() const;
    
    /**
     * @brief peekPriority
     * O(1)
     * @return 
     */
    int peekPriority() const;
    
    /**
     * @brief size
     * O(1)
     * @return 
     */
    int size() const;
    
    /**
     * @brief operator <<
     * O(n)
     * @param out
     * @param queue
     * @return 
     */
    friend ostream& operator <<(ostream& out, const HeapPriorityQueue& queue);

private:
    PQEntry *arr; // pointer to first elem of the array
    int arrSize; // number of elements
    int capacity; // size of the array
    
    /**
     * @brief resize
     * Creates new array with given capacity and copies old array's contents over.
     * @param newCapacity
     */
    void resize(int newCapacity);
    
    /**
     * @brief bubbleDown
     * Recursively bubbles given entry down the binary heap to less urgent territory. 
     * Used for dequeue.
     * @param parentIndex - starting parent index of entry to bubble down
     * @param currIndex - current index of entry to bubble down
     */
    void bubbleDown(int parentIndex, int currIndex);
    
    /**
     * @brief bubbleUp
     * Bubbles given entry up the binary heap to more urgent territory. Used for enqueue
     * and change priority.
     * @param currIndex - current index of entry to bubble up
     * @param parentIndex - starting parent index of entry to bubble up
     * @param entry - the entry itself
     */
    void bubbleUp(int currIndex, int parentIndex, PQEntry entry);
    
    /**
     * @brief search
     * Uses recursive backtracking to search for a given entry with a priority less urgent
     * than newPriority.
     * @param value - value of entry it is looking for
     * @param currIndex - index of entry currently being look at
     * @param returnIndex - passed by reference, set to valid found entry's index.
     * @param newPriority - should be more urgent than found entry's priority
     * @return - returns whether search was successful
     */
    bool search(string value, int currIndex, int &returnIndex, int newPriority);
};

#endif
