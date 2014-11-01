#include "VectorPriorityQueue.h"

VectorPriorityQueue::VectorPriorityQueue() {

}

VectorPriorityQueue::~VectorPriorityQueue() {

}

void VectorPriorityQueue::changePriority(string value, int newPriority) {
    try {
        PQEntry *entry;
        for (int i = 0; i < priorityQueue.size(); i++) { // loop through vector
            entry = &priorityQueue[i];
            if (entry->value == value) {
                if (entry->priority < newPriority) {
                    error("existing priority is higher");
                } else {
                    entry->priority = newPriority;
                    entry = NULL;
                    return;
                }
            }
        }
        error("value not found");
    } catch (ErrorException& error) {
        
    }
}

int VectorPriorityQueue::getMostUrgentElement() const {
    // setup 
    int mostUrgentIndex = 0;
    PQEntry mostUrgentEntry = priorityQueue[mostUrgentIndex];
    PQEntry currentEntry;
    
    for (int i = 0; i < priorityQueue.size(); i++) { // for each element
        currentEntry = priorityQueue[i];
        // compare with most urgent and update if needed
        if (mostUrgentEntry > currentEntry) { 
            mostUrgentIndex = i;
            mostUrgentEntry = priorityQueue[mostUrgentIndex];
        }
    }
    
    return mostUrgentIndex;
}

void VectorPriorityQueue::clear() {
    priorityQueue.clear();
}

string VectorPriorityQueue::dequeue() {
    string value;
    try {
        if (priorityQueue.isEmpty()) {
            error("priority queue is empty");
            value = "";
        } else {
            int mostUrgentIndex = getMostUrgentElement(); // get most urgent element's index
            value = priorityQueue[mostUrgentIndex].value; // store value
            priorityQueue.remove(mostUrgentIndex); // remove most urgent element
        }
    } catch (ErrorException& error) {
        return "";
    }
    return value; // return value
}

void VectorPriorityQueue::enqueue(string value, int priority) {
    PQEntry newEntry = PQEntry(value, priority);
    priorityQueue.add(newEntry);
}

bool VectorPriorityQueue::isEmpty() const {
    return priorityQueue.isEmpty();
}

string VectorPriorityQueue::peek() const {
    try {
        if (priorityQueue.isEmpty()) {
            error("priority queue is empty");
            return "";
        } else {
            int mostUrgentIndex = getMostUrgentElement();
            return priorityQueue[mostUrgentIndex].value;
        }
    } catch (ErrorException& error) {
        return "";
    }
}

int VectorPriorityQueue::peekPriority() const {
    try {
        if (priorityQueue.isEmpty()) {
            error("priority queue is empty");
            return 0;
        } else {
            int mostUrgentIndex = getMostUrgentElement();
            return priorityQueue[mostUrgentIndex].priority;
        }
    } catch (ErrorException& error) {
        return 0;
    }
}

int VectorPriorityQueue::size() const {
    return priorityQueue.size();
}

PQEntry VectorPriorityQueue::getElemAtIndex(int index) const {
    return priorityQueue[index];
}

ostream& operator<<(ostream& out, const VectorPriorityQueue& queue) {
    out << "{";
    for (int i = 0; i < queue.size(); i++) {
        out << queue.getElemAtIndex(i);
        if (i < queue.size() - 1) out << ", "; // if not the last element
    }
    out << "}";
    return out;
}
