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
    // TODO: implement

}

void VectorPriorityQueue::clear() {
    // TODO: implement

}

string VectorPriorityQueue::dequeue() {
    // TODO: implement
    return "";   // remove this
}

void VectorPriorityQueue::enqueue(string value, int priority) {
    // TODO: implement

}

bool VectorPriorityQueue::isEmpty() const {
    // TODO: implement
    return false;   // remove this
}

string VectorPriorityQueue::peek() const {
    // TODO: implement
    return "";   // remove this
}

int VectorPriorityQueue::peekPriority() const {
    // TODO: implement
    return 0;   // remove this
}

int VectorPriorityQueue::size() const {
    // TODO: implement
    return 0;   // remove this
}

ostream& operator<<(ostream& out, const VectorPriorityQueue& queue) {
    // TODO: implement
    return out;
}
