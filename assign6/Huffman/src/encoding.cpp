// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
#include "pqueue.h"
#include "vector.h"

// helper functions
void makePriorityQueue(PriorityQueue<HuffmanNode*>& pqueue, const Map<int, int>& freqTable); 
void makeTree(PriorityQueue<HuffmanNode*>& pqueue);

/**
 * @brief buildFrequencyTable
 * Counts frequency of characters in an input (string or file), puts them
 * in a map, and returns the map when it reaches the end of the file. Assumes 
 * input file exists and can be read. 
 * @param input - valid input (string or file) from user
 * @return - map of frequency of each character
 */
Map<int, int> buildFrequencyTable(istream& input) {
    // init variables
    Map<int, int> freqTable;
    bool endOfFile = false;
    char currCharacter;
    
    // count character frequencies
    while (!endOfFile) {
        currCharacter = input.get();
        if (currCharacter == -1) { // end of file
            endOfFile = true;
            freqTable.put(PSEUDO_EOF, 1);
        } else { // otherwise, valid character
            freqTable[currCharacter]++;
        }
    }
    
    return freqTable;
}

HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    PriorityQueue<HuffmanNode*> pqueue;
    makePriorityQueue(pqueue, freqTable);
    makeTree(pqueue);
    
    return pqueue.peek();   // this is just a placeholder so it will compile
}

void makeTree(PriorityQueue<HuffmanNode*>& pqueue) {
    while (pqueue.size() > 1) {
        // dequeue first two nodes, store in left and right
        HuffmanNode* left = pqueue.dequeue();
        HuffmanNode* right = pqueue.dequeue();
        
        // make new parent node with children attached
        int countSum = left->count + right->count;
        HuffmanNode* parent = new HuffmanNode(NOT_A_CHAR, countSum, left, right);
        
        // enqueue parent
        pqueue.enqueue(parent, countSum);
    }
}

void makePriorityQueue(PriorityQueue<HuffmanNode*>& pqueue, const Map<int, int>& freqTable) {
    Vector<int> keys = freqTable.keys();
    
    for (int key : keys) {
        HuffmanNode* node = new HuffmanNode(key, freqTable[key]);
        pqueue.enqueue(node, freqTable[key]);
    }
}


Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    // TODO: implement this function
    Map<int, string> encodingMap;   // this is just a placeholder so it will compile
    return encodingMap;             // this is just a placeholder so it will compile
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    // TODO: implement this function
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
