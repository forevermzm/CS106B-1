/*
 * CS106B Assignment 2 Part 1, Word Ladders
 * Claire Huang
 */

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "set.h"
#include "simpio.h"
#include "map.h"
#include "queue.h"
#include "stack.h"
#include "filelib.h"
#include "strlib.h"

using namespace std;

void printWelcome();
void setupDictionary(Set<string> &dictionary);
bool promptUser();
void findWordLadder();
void findNeighbors(Vector<string> &neighbors, Set<string> &usedWords, string word);
void printStack(Stack<string> &stack);

Set<string> dictionary;
string startWord, endWord;

int main() {
    printWelcome();
    setupDictionary(dictionary);

    while(promptUser()) {
        findWordLadder();
    }

    cout << "Have a nice day." << endl;
    return 0;
}

/**
 * @brief printWelcome
 * Prints welcome message.
 */
void printWelcome() {
    cout << "Welcome to CS 106B Word Ladder." << '\n'
         << "Please give me two English words, and I will change the" << '\n'
         << "first into the second by changing one letter at a time." << endl << endl;
}

/**
 * @brief setupDictionary
 * Reads dictionary.txt file and fills in passed in set with
 * the file's list of words.
 * @param set
 */
void setupDictionary(Set<string> &set) {
    ifstream stream;
    openFile(stream, "dictionary.txt");

    string word;
    while(true) {
        getline(stream, word);
        set.add(word);
        if (stream.fail()) break; // reached end of document
    }
}

/**
 * @brief promptUser
 * Prompts user for 2 words and reprompts until valid words
 * are given. Returns whether program should continue executing.
 * @return 
 */
bool promptUser() {
    startWord = getLine("Word #1: (or Enter to quit): ");
    if (startWord.empty()) return false; // if "Enter to quit"
    startWord = toLowerCase(startWord);
    
    // check start word for valid input (is English word?)
    while(true) {
        if (dictionary.contains(startWord)) break;
        startWord = getLine("That's not an English word. Try again: ");
    }
    
    endWord = getLine("Word #2: (or Enter to quit): ");
    if (endWord.empty()) return false; // if "Enter to quit"
    endWord = toLowerCase(endWord);
        
    // check end word for valid input (is English word? is not start word? is same length as start word?)
    while(true) {
        if (dictionary.contains(endWord) && endWord != startWord && endWord.length() == startWord.length()) break;
        endWord = getLine("Invalid input. Try again: ");
    }
    
    return true;
}

/**
 * @brief findWordLadder
 * Loops through queue of word ladder stacks. Removes topmost word
 * from ladder, finds its neighbors, and if they aren't the end
 * word, creates a copy of the ladder for each neighbor and adds the
 * copies to the queue. Prints either the final word ladder or that 
 * no ladders could be found.
 */
void findWordLadder() {
    // setup
    Queue<Stack<string> > ladders;
    Set<string> usedWords;
    Stack<string> currentLadder, tempLadder;

    // fill and add first ladder
    Stack<string> ladder;
    ladder.push(startWord);
    ladders.enqueue(ladder);

    // add start word to used words set
    usedWords.add(startWord);

    while(!ladders.isEmpty()) {
        currentLadder = ladders.dequeue(); // get topmost ladder
        string currentWord = currentLadder.peek(); // peek at topmost word
        Vector<string> neighbors;
        findNeighbors(neighbors, usedWords, currentWord);

        for (int i = 0; i < neighbors.size(); i++) { // for each neighbor
            if (neighbors[i] == endWord) { // final word ladder is found!
                currentLadder.push(endWord);
                cout << "A ladder from " << endWord << " back to " << startWord << ":" << endl;
                printStack(currentLadder);
                return;
            } else { // make copy of ladder with neighbor and add to queue
                tempLadder = currentLadder;
                tempLadder.push(neighbors[i]);
                ladders.enqueue(tempLadder);
            }
        }
    }
    
    cout << "No word ladder found from " << endWord << " back to " << startWord << "." << endl << endl;
    return;
}

/**
 * @brief findNeighbors
 * Finds all valid English and unused neighbors of a word
 * and puts them in the passed in Vector.
 * @param neighbors
 * @param usedWords
 * @param word
 */
void findNeighbors(Vector<string> &neighbors, Set<string> &usedWords, string word) {
    for (int i = 0; i < word.length(); i++) { // for each letter in the word
        for (char letter = 'a'; letter <= 'z'; letter++) { // for each letter in alphabet
            if (word[i] != letter) { // don't want the same word
                string temp = word;
                temp[i] = letter;
                if (dictionary.contains(temp) && !usedWords.contains(temp)) {   
                    neighbors.add(temp);
                    usedWords.add(temp);
                }
            }
        }
    }
}

/**
 * @brief printStack
 * Prints final word ladder stack.
 * @param stack
 */
void printStack(Stack<string> &stack) {
    while(!stack.isEmpty()) {
        cout << stack.pop() << " ";
    }
    cout << endl << endl;
}
