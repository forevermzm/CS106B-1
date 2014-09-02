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
#include "random.h"

using namespace std;

void printWelcomeMessage();
void setup();
void setupMap(ifstream &stream);
void tokenScanner(Queue<string> &tokens, string line);
string nextToken(ifstream &stream, Queue<string> &tokens, string line);
string queueToString(Queue<string> queue);
string generateRandomText(int requestedNumWords);

int n;
Map<string, Vector<string> > wordsMap;

int main() {
    printWelcomeMessage();
    
    setup(); // prompt user and fill in map
    
    while(true) {
        cout << endl;
        int numWords = getInteger("# of random words to generate (0 to quit)?: ");
        if (numWords == 0) break;
        
        if (numWords >= n) {
            cout << generateRandomText(numWords) << endl;    
        } else {
            cout << "Must be greater than or equal to " << n << "." << endl;
        }
    }
        
    cout << "Exiting." << endl;
    return 0;
}

void printWelcomeMessage() {
    cout << "Welcome to CS 106B Random Writer ('N-Grams')." << endl
         << "This program makes random text based on a document." << endl
         << "Give me an input file and an 'N' value for groups" << endl
         << "of words, and I'll create random text for you." << endl << endl;
}

/**
 * @brief setup
 * Prompts user for input file and number of words in each n-gram,
 * and passes the information along to the map setup function.
 */
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

/**
 * @brief setupMap
 * Reads in provided file and fills in map with keys (string of n-1 words) and
 * their values (vector of words that follow the key).
 * @param stream
 */
void setupMap(ifstream &stream) {
    Queue<string> window, wrapAround;
    string line, windowString, nextWord;
    Vector<string> tempVector;
    Queue<string> tokens;
    
    // add up enough words for the first window and first n words for use when map wraps around the file
    // can assume n < total # words in file (won't reach end of file here)
    for (int i = 0; i < n; i++) {
        wrapAround.enqueue(nextToken(stream, tokens, line));
    }
    
    // first window
    window = wrapAround;
    window.dequeue(); // one too many words remembered
    
    while(true) {
        // get next word
        nextWord = nextToken(stream, tokens, line);
        if(stream.fail()) nextWord = wrapAround.dequeue(); // if end of file, read from wrap around queue
        if(wrapAround.isEmpty()) break; // no more wrap around words
        
        // add window and next token to map
        windowString = queueToString(window);
        tempVector = wordsMap[windowString]; // get existing vector
        tempVector.add(nextWord);
        wordsMap.put(windowString, tempVector);
                
        // make next window
        window.enqueue(nextWord);
        if(window.size() > (n-1)) window.dequeue(); // if window is larger than proper size 
    }
}

/**
 * @brief nextToken
 * Manages reading in and chopping up each line. Returns the next word in the
 * given file or the empty string once there are no more tokens to be read.
 * @param stream
 * @param tokens
 * @param line
 * @return 
 */
string nextToken(ifstream &stream, Queue<string> &tokens, string line) {
    while(tokens.size() <= 0) { // if no more tokens left, read a new line
        line = ""; // empty the line
        getline(stream, line);
        if (stream.fail()) return ""; // stop if at end of file
        tokenScanner(tokens, line); // split into individual words
    }
    return tokens.dequeue();
}

/**
 * @brief tokenScanner
 * Returns queue of words (tokens, puncutation included, no spaces) in a given line.
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

/**
 * @brief queueToString
 * Returns string with space-separated contents of a given queue.
 * @param queue
 * @return 
 */
string queueToString(Queue<string> queue) {
    string str;
    
    while(true) {
        str += queue.dequeue() + " ";
        if (queue.isEmpty()) break;
    }
    
    return str;
}

/**
 * @brief generateRandomText
 * Generates the given number of random words by picking a random
 * (n-1)-word key from the map to start and randomly picking the next
 * word from the key's values.
 * @param requestedNumWords
 * @return 
 */
string generateRandomText(int requestedNumWords) {
    string output = "...";
    string nextWord;
    int generatedNumWords = 0;
    Vector<string> possibleNextWords;
    Queue<string> window;
    
    // select random key and put it in window
    string start = wordsMap.keys().get(randomInteger(0, wordsMap.size() - 1));
    output += start;
    generatedNumWords += (n-1);
    tokenScanner(window, start); // put it in window
    
    while(true) {
        // get random next word based on window contents
        possibleNextWords = wordsMap.get(queueToString(window));
        nextWord = possibleNextWords.get(randomInteger(0, possibleNextWords.size() - 1));
        output += nextWord + " ";
        generatedNumWords++;
        
        if (generatedNumWords >= requestedNumWords) break;
        
        // add onto window and dequeue
        window.enqueue(nextWord);
        window.dequeue();
    }
    
    output += "...";
    
    return output;
}
