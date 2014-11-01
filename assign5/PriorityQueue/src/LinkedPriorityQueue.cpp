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
    clear();
}

void LinkedPriorityQueue::changePriority(string value, int newPriority) {
    ListNode* prev = NULL;
    try {
        for (ListNode* curr = head; curr != NULL; curr = curr->next) { // for each elem
            if (value == curr->value && newPriority < curr->priority) { // if valid entry, delete it
                if (prev == NULL) { // if should be inserted as first element, change head
                    head = curr->next;
                } else { // otherwise change prev
                    prev->next = curr->next;
                }
                enqueue(value, newPriority); // put new entry with new priority
                return; // stop looking
            }
            prev = curr; // move prev along
        }
        error("couldn't find a matching value with greater priority");
    } catch (ErrorException& error) {
        return;
    }
}

void LinkedPriorityQueue::clear() {
    if (isEmpty()) return;
    
    ListNode *current = head;
    ListNode *next = NULL;
    
    // while not at the end of the linked list, delete each entry
    while (current != NULL) { 
        next = current->next;
        delete current;
        current = next;
    }
    
    head = NULL;
}

string LinkedPriorityQueue::dequeue() {
    string returnString;
    
    try {
        if (isEmpty()) error("dequeuing from an empty PQ");
        
        // remove first element
        ListNode *dequeue = head;
        head = dequeue->next;
        returnString = dequeue->value;
        delete dequeue;
        
    } catch (ErrorException &error) {
        returnString = "";
    }
    
    return returnString;
}

void LinkedPriorityQueue::enqueue(string value, int priority) {
    ListNode *newNode = new ListNode(value, priority);
    ListNode *curr = head;
    ListNode *prev = NULL;
    
    // find proper sorted place to insert new element
    for (curr = head; curr != NULL; curr = curr->next) {
        if (*newNode <= *curr) {
            break;
        }
        prev = curr;
    }
    
    // rewire pointers to insert
    newNode->next = curr; // outgoing pointer
    if (prev == NULL) { // incoming pointer
        head = newNode;
    } else {
        prev->next = newNode;
    }
}

bool LinkedPriorityQueue::isEmpty() const {
    return (head == NULL);
}

string LinkedPriorityQueue::peek() const {
    try {
        if (isEmpty()) error("peeking at an empty PQ");
        return head->value;
    } catch (ErrorException &error) {
        return "";
    }
}

int LinkedPriorityQueue::peekPriority() const {
    try {
        if (isEmpty()) error("peeking at an empty PQ");
        return head->priority;
    } catch (ErrorException &error) {
        return 0;
    }
}

int LinkedPriorityQueue::size() const {
    int size = 0;
    for (ListNode* curr = head; curr != NULL; curr = curr->next) {
        size++;
    }
    return size;
}

ostream& operator<<(ostream& out, const LinkedPriorityQueue& queue) {
    out << "{";
    for (ListNode *curr = queue.head; curr != NULL; curr = curr->next) {
        out << *curr;
        if (curr->next != NULL) out << ", ";
    }
    out << "}";
    return out;
}
