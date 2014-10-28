// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "LinkedPriorityQueue.h"

LinkedPriorityQueue::LinkedPriorityQueue() {
    head = NULL;
}

LinkedPriorityQueue::~LinkedPriorityQueue() {
    ListNode *current = head;
    ListNode *next = NULL;
    
    while (current != NULL) {
        next = current->next;
        delete current;
        current = next;
    }
}

void LinkedPriorityQueue::changePriority(string value, int newPriority) {
    // TODO: implement

}

void LinkedPriorityQueue::clear() {
    // TODO: implement

}

string LinkedPriorityQueue::dequeue() {
    // TODO: implement
    return "";   // remove this
}

void LinkedPriorityQueue::enqueue(string value, int priority) {
    ListNode newNode = ListNode(value, priority);
    
}

bool LinkedPriorityQueue::isEmpty() const {
    // TODO: implement
    return false;   // remove this
}

string LinkedPriorityQueue::peek() const {
    // TODO: implement
    return "";   // remove this
}

int LinkedPriorityQueue::peekPriority() const {
    // TODO: implement
    return 0;   // remove this
}

int LinkedPriorityQueue::size() const {
    // TODO: implement
    return 0;   // remove this
}

ostream& operator<<(ostream& out, const LinkedPriorityQueue& queue) {
    // TODO: implement
    return out;
}
