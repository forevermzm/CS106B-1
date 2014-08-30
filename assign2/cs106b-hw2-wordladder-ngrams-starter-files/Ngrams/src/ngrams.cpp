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
string nextToken(ifstream &stream, Queue<string> &tokens, string line);

int n;
Map<string, Vector<string> > wordsMap;

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
    string line, windowString;
    string currentToken;
    Queue<string> tokens;
    
    // add up enough words for the first window
    // can assume n < total # words in file (won't reach end of file here)
    for (int i = 0; i < (n-1); i++) {
        window.enqueue(nextToken(stream, tokens, line));
    }
    
    // first window
    windowString = queueToString(window);
    if (wordsMap[windowString] == NULL) wordsMap[windowString] = Vector<String>();
    wordsMap.put(windowString, wordsMap[windowString].add(window.peek()));
    
    cout << windowString << endl;
    
    while(tokens.size() > 0) { // while there are tokens left
        window.enqueue(nextToken(stream, tokens, line));
        if(stream.fail()) break; // end of file
        if(window.size() > (n-1)) window.dequeue(); // if window is larger than proper size   
        windowString = queueToString(window);
        if (wordsMap[windowString] == NULL) wordsMap[windowString] = Vector<String>();
        wordsMap.put(windowString, wordsMap[windowString].add(window.peek()));
    }
}

string nextToken(ifstream &stream, Queue<string> &tokens, string line) {
    while(tokens.size() <= 0) { // if no more tokens left, read a new line
        line = ""; // empty the line
        getline(stream, line);
        if (stream.fail()) return; // stop if at end of file
        tokenScanner(tokens, line); // split into individual words
    }
    return tokens.dequeue();
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

