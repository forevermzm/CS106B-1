// .h file of Boggle class. Implements functions that keep track
// of data from the two players of a game and searches the board
// for particular words for both players.

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "vector.h"
#include "strlib.h"
#include "shuffle.h"
#include "random.h"
#include "stack.h"

using namespace std;

class Boggle {
public:
    /**
     * @brief Boggle::Boggle
     * Boggle class constructor. Sets up a randomly or user generated initial
     * board state and sets up dictionary.
     * @param dictionary - Lexicon passed in by reference from bogglemain.cpp.
     * Boggle class copies reference to Lexicon for use in the rest of the class.
     * @param boardText - Guaranteed a valid, all caps, 16 character long
     * string of letters OR an empty string (signifying the user wants a 
     * random board).
     */
    Boggle(Lexicon& dictionary, string boardText = "");
    
    /**
     * @brief Boggle::getLetter
     * Gets letter from Boggle board at specified row and column.
     * If row or column is out of bounds, throws an exception and 
     * returns an empty character.
     * @param row - row
     * @param col - column
     * @return - Return specified letter from Boggle board or empty
     * character if location cannot be accessed.
     */
    char getLetter(int row, int col);
    
    /**
     * @brief Boggle::checkWord
     * Returns if user inputted word is suitable to search for
     * on the Boggle board. Checks if input is long enough, if
     * input if a valid English word, and if input has already
     * been used by the human.
     * @param word - User inputted word. Guaranteed to be lower
     * case.
     * @return - Returns whether or not word is worth searching
     * the Boggle board for.
     */
    bool checkWord(string word);
    
    /**
     * @brief Boggle::humanWordSearch
     * Wrapper function for recursive search on boggle board for
     * human-inputted word. Sets up Boggle state for each search and 
     * only searches if the word is okay to search for (based on 
     * checkWord's output). Then handles scoring once word has been
     * found on the board.
     * @param word - User inputted word. Guaranteed to be lower case.
     * @return - Returns whether valid word was found on the board.
     */
    bool humanWordSearch(string word);
    
    /**
     * @brief Boggle::humanScore
     * Returns human's score.
     * @return 
     */
    int humanScore();
    
    /**
     * @brief Boggle::computerWordSearch
     * Wrapper function for computer's recursive backtracking search function.
     * @return - Set of all words that the computer found in alphabetical order.
     */
    Set<string> computerWordSearch();
    
    /**
     * @brief Boggle::getScoreComputer
     * Returns computer's score.
     * @return 
     */
    int getScoreComputer();
    
    /*-------------------------------------------------------------------------*/
    
    /**
     * @brief Boggle::getCurrentBoard
     * Returns string of letters on the Boggle board. For use in setting
     * up the initial boggle gui board.
     * @return - string of letters on the Boggle board.
     */
    string getCurrentBoard();
    
    /**
     * @brief Boggle::getNumHumanWords
     * Returns size of the set of words human has found.
     * @return 
     */
    int getNumHumanWords();
    
    /**
     * @brief Boggle::getHumanWords
     * Returns string represetation of set of words human has found.
     * @return 
     */
    string getHumanWords();
    
    /**
     * @brief BOARD_SIZE
     * Constant for size of the board for scalability of the game.
     */
    static const int BOARD_SIZE = 16;

private:
    /**
     * @brief Boggle::recursiveHumanSearch
     * Searches the board for the inputted word using recursive backtracking.
     * Chooses a square to search from based on list of all available squares
     * from the current location, then tries to solve from there and backs up
     * if needed.
     * @param word - User inputted word, guaranteed to be lower case and valid.
     * @param currIndex - Index of the current square (indexed from 0-15 based
     * on string representation of board).
     * @return - Returns whether the word was found.
     */
    bool findWordOnBoard(string word, int currIndex);
    
    /**
     * @brief Boggle::findAllWordsOnBoard
     * Computer's recursive backtracking search function to find all valid words
     * on the Boggle board. Prunes search tree by checking whether the currWord is 
     * a valid prefix in the dictionary. Base case is when the topmost layer of the
     * recursive tree has reached the end of the boggle board (index 16).
     * @param foundWords - Set of words that the computer has found on the board.
     * @param currIndex - Current index on the board that the computer is checking from.
     * @param currWord - Current word that the computer has pieced together from the squares
     * it has visited.
     * @return - Returns true when the search is complete. 
     */
    bool findAllWordsOnBoard(Set<string>& foundWords, int currIndex, string currWord);
    
    /**
     * @brief Boggle::availableSquares
     * Returns a vector of all the neighboring square indexes based on the current
     * location on the board.
     * @param currIndex - Current location on the board. If -1, then searching has not
     * started yet, so return the indexes of the entire board.
     * @return - Vector of neighboring squares' indexes
     */
    Vector<int> availableSquares(int currIndex);
    
    string board;
    Lexicon boggleDictionary;
    Set<string> humanWords;
    int humansScore;
    int computersScore;
    Set<int> chosenHumanSquares;
    Set<int> chosenComputerSquares;
};

/**
 * @brief operator <<
 * Prints board in 4x4 format when cout-ed to the console.
 * @param out
 * @param boggle
 * @return 
 */
ostream& operator<<(ostream& out, Boggle& boggle);

#endif // _boggle_h
