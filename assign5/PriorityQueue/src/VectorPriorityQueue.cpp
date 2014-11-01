// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "VectorPriorityQueue.h"

VectorPriorityQueue::VectorPriorityQueue() {
    // TODO: implement

}

VectorPriorityQueue::~VectorPriorityQueue() {
    // TODO: implement

}

void VectorPriorityQueue::changePriority(string value, int newPriority) {
    cout << "changing priority" << endl;
    try {
        PQEntry *entry;
        for (int i = 0; i < priorityQueue.size(); i++) {
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
    int mostUrgentIndex = 0;
    PQEntry mostUrgentEntry = priorityQueue[mostUrgentIndex];
    PQEntry currentEntry;
    
    for (int i = 0; i < priorityQueue.size(); i++) {
        currentEntry = priorityQueue[i];
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
            int mostUrgentIndex = getMostUrgentElement();
            value = priorityQueue[mostUrgentIndex].value;
            priorityQueue.remove(mostUrgentIndex);
        }
    } catch (ErrorException& error) {
        return "";
    }
    return value;
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
        out << queue.priorityQueue[i];
        if (i < queue.size() - 1) out << ", ";
    }
    out << "}";
    return out;
}
