// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "HeapPriorityQueue.h"

HeapPriorityQueue::HeapPriorityQueue() {
    arrSize = 0;
    capacity = 2;
    arr = new PQEntry[capacity];
}

HeapPriorityQueue::~HeapPriorityQueue() {
    delete[] arr;
}

void HeapPriorityQueue::resize(int newCapacity) {
    if (arrSize + 1 <= capacity - 1) return; // if won't go off end of array after adding one elem, don't resize
    
    PQEntry *biggerArray = new PQEntry[newCapacity];    
    for (int i = 0; i < capacity; i++) {
        biggerArray[i] = arr[i];
    }
    
    delete[] arr; // delete old small array
    
    arr = biggerArray; // assign array pointer to new big array
    capacity = newCapacity; 
}

void HeapPriorityQueue::changePriority(string value, int newPriority) {
    int returnIndex;
    try {
        if (search(value, 1, returnIndex, newPriority)) {
            arr[returnIndex].priority = newPriority;
            bubbleUp(returnIndex, returnIndex / 2, arr[returnIndex]);
        } else {
            error("PQEntry with valid value and priority not found.");
        }
    } catch (ErrorException &error) {
        cout << "PQEntry with valid value and priority not found." << endl;
    }
}

bool HeapPriorityQueue::search(string value, int currIndex, int &returnIndex, int newPriority) {
    if (currIndex > arrSize) return false; // no more choices
    if (arr[currIndex].value == value) { // found
        if (arr[currIndex].priority < newPriority) return false;
        returnIndex = currIndex;
        return true;
    }
    
    for (int i = 0; i < 2; i++) { // for the two child indexes
        int childIndex = currIndex * 2 + i; // try one choice
        if (search(value, childIndex, returnIndex, newPriority)) return true; // solve from here
        // otherwise unmake choice
    }
    
    return false;
}

void HeapPriorityQueue::clear() {
    delete[] arr; // delete old array TODO: POINTER BEING FREED WAS NOT ALLOCATED
    arr = new PQEntry[capacity]; // create new empty array with same capacity
    
    arrSize = 0; // reset size
}

string HeapPriorityQueue::dequeue() {
    PQEntry dequeue = arr[1];
    arr[1] = arr[arrSize];
    
    arrSize--;
    
    bubbleDown(1, 1);
    
    return dequeue.value;
}

void HeapPriorityQueue::bubbleDown(int parentIndex, int currIndex) {
    // if at end of array or child is in the right place
    if (currIndex > arrSize || arr[currIndex] > arr[parentIndex]) return;
    
    // swap
    if (currIndex != 1) {
        PQEntry temp = arr[currIndex];
        arr[currIndex] = arr[parentIndex];
        arr[parentIndex] = temp;
    }
    
    bubbleDown(currIndex, currIndex * 2);
    bubbleDown(currIndex, currIndex * 2 + 1);
}

void HeapPriorityQueue::enqueue(string value, int priority) {
    // TODO: enqueue crashes after a clear
    resize(capacity + 5); // resize if necessary
    
    PQEntry newEntry = PQEntry(value, priority);
    arr[arrSize + 1] = newEntry; // put in first empty index
    
    int currIndex = arrSize + 1;
    int parentIndex = currIndex / 2;
    
    arrSize++;
    
    if (currIndex == 1) return; // first element, don't do anything
    
    bubbleUp(currIndex, parentIndex, newEntry);
}

void HeapPriorityQueue::bubbleUp(int currIndex, int parentIndex, PQEntry entry) {
    while(arr[parentIndex] > arr[currIndex]) {
        if (currIndex == 1) return; // at beginning of array
        
        // swap
        arr[currIndex] = arr[parentIndex];
        arr[parentIndex] = entry;
        
        // update indexes
        currIndex = parentIndex;
        parentIndex = currIndex / 2;
    }
}

bool HeapPriorityQueue::isEmpty() const {
    return (arrSize == 0);
}

string HeapPriorityQueue::peek() const {
    if (isEmpty()) return "";
    return arr[1].value;
}

int HeapPriorityQueue::peekPriority() const {
    if (isEmpty()) return 0;
    return arr[1].priority;
}

int HeapPriorityQueue::size() const {
    return arrSize;
}

ostream& operator<<(ostream& out, const HeapPriorityQueue& queue) {
    out << "{";
    for (int i = 1; i <= queue.arrSize; i++) {
        out << queue.arr[i];
        if (i < queue.arrSize) out << ", ";
    }
    out << "}";
    return out;
}
