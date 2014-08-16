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
void printQueue(Queue<string> &queue);
void tokenScanner(Vector<string> &tokens, string line);

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
    
    setupMap(stream);
}

void setupMap(ifstream &stream) {
    TokenScanner scanner(stream);
    scanner.ignoreWhitespace();
    Queue<string> window, tempWindow;
    string nextToken, prevToken;
    
//    for (int i = 0; i < (n-1); i++) {
//        if (!scanner.hasMoreTokens()) break;
//        window.enqueue(scanner.nextToken());
//    }
    
//    while(scanner.hasMoreTokens()) {
//        string nextToken = scanner.nextToken();
//        // add spaces
//        if (nextToken != "." && nextToken != "\'" && nextToken != "?" 
//                && nextToken != "," && nextToken != "!" && prevToken != "\'") {
//            nextToken = " " + nextToken;
//        }
//        cout << nextToken;
//        prevToken = nextToken;
//        window.enqueue(nextToken);
        
//        if (window.size() > (n-1)) {
//            window.dequeue();
//        }
        
//        tempWindow = window;
//        printQueue(tempWindow);
//    }
    
    string line;
    while(true) {
        getline(stream, line);
        if(stream.fail()) break;
        Vector<string> tokens;
        tokenScanner(tokens, line);
        for (int i = 0; i < tokens.size(); i++) {
            cout << tokens[i] << " ";
        }
    }
}

void tokenScanner(Vector<string> &tokens, string line) {
    line = trim(line);
    if(line == "") return; // empty line
    
    int lastPosition = 0;
    int foundPosition = 0;
    
    while(true) {
        foundPosition = line.find(" ", lastPosition);
        if(foundPosition == string::npos) {
            tokens.add(line.substr(lastPosition, string::npos));
            break;
        }
        tokens.add(line.substr(lastPosition, foundPosition - lastPosition));
        lastPosition = foundPosition + 1;   
    }
}

void printQueue(Queue<string> &queue) {
    while(!queue.isEmpty()) {
        cout << queue.dequeue();
    }
    cout << endl;
}
