#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "map.h"
#include "vector.h"
#include "strlib.h"
#include "queue.h"
#include "tokenscanner.h"

using namespace std;

void printWelcomeMessage();
void setup();
void setupMap(ifstream &stream);
string queueToString(Queue<string> queue);
void tokenScanner(Queue<string> &tokens, string line);
bool readLineFromFile(ifstream &stream, Queue<string> &tokens, string line);

int n;
Map<string, Vector<string> > map;

int main() {
    printWelcomeMessage();
    
    setup();
    
    cout << "Exiting." << endl;
    return 0;
}

void printWelcomeMessage() {
    cout << "Welcome to CS 106B Random Writer ('N-Grams')." << endl
         << "This program makes random text based on a document." << endl
         << "Give me an input file and an 'N' value for groups" << endl
         << "of words, and I'll create random text for you." << endl << endl;
}

void setup() {
    // prompt user for input file
    string filename;
    ifstream stream;
    while(true) {
        filename = getLine("Input file name? ");
        if(fileExists(filename)) {
            openFile(stream, filename);
            break;
        }
        cout << "Couldn't open that file. Please try again." << endl;
    }
    
    // prompt user for n
    while(true) {
        n = getInteger("Value of N? ");
        if(n >= 2) break;
        cout << "Please enter an integer greater than 1." << endl;
    }
    
    // create and fill map of n words (key) and Vector of words that follow (value)
    setupMap(stream);
}

void setupMap(ifstream &stream) {
    Queue<string> window;
    string line;
    string currentToken;
    Queue<string> tokens;
    
    // get enough words to open first window
    while(tokens.size() < n) {
        if (!readLineFromFile(stream, tokens, line)) return; // reached end of file
    }
    
    // add up enough words for the first window
    for (int i = 0; i < (n-1); i++) {
        window.enqueue(tokens.dequeue());
    }
    
    cout << queueToString(window) << endl;
    
    while(tokens.size() > 0) { // while there are tokens left
        window.enqueue(tokens.dequeue());
        if(window.size() > (n-1)) window.dequeue();
        cout << queueToString(window) << endl;
    }
}

/**
 * @brief readLineFromFile
 * Reads a line from input file and fills queue of tokens. Returns whether it's 
 * ok to keep reading lines.
 * @param stream
 * @param tokens
 * @param line
 * @return 
 */
bool readLineFromFile(ifstream &stream, Queue<string> &tokens, string line) {
    line = ""; // empty the line
    getline(stream, line);
    if (stream.fail()) return false;
    tokenScanner(tokens, line); // split into individual words
    return true;
}

/**
 * @brief tokenScanner
 * Returns queue of words (tokens, puncutation included, no spaces) 
 * in a given line.
 * @param tokens
 * @param line
 */
void tokenScanner(Queue<string> &tokens, string line) {
    line = trim(line); // remove trailing whitespace
    if(line == "") return; // empty line
    
    int lastPosition = 0;
    int foundPosition = 0;
    
    while(true) {
        foundPosition = line.find(" ", lastPosition);
        if(foundPosition == string::npos) { // reached end of the line
            tokens.enqueue(line.substr(lastPosition, string::npos)); // get the last word
            break;
        }
        tokens.enqueue(line.substr(lastPosition, foundPosition - lastPosition));
        lastPosition = foundPosition + 1;   
    }
}

string queueToString(Queue<string> queue) {
    string key;
    
    while(!queue.isEmpty()) {
        key += queue.dequeue() + " ";
    }

    return key;    
}

