// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Boggle.h"
#include <cmath>
#include "error.h"
#include "bogglegui.h"

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

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
Boggle::Boggle(Lexicon& dictionary, string boardText) {
    if (boardText.empty()) { // generate random board
        shuffle(CUBES, BOARD_SIZE);
        for (int i = 0; i < BOARD_SIZE; i++) {
            board += (CUBES[i][randomInteger(0, 5)]);
        }
    } else if (boardText.length() == BOARD_SIZE) { // generate board from input text
        for (int i = 0; i < BOARD_SIZE; i++) {
            board += (boardText[i]);
        }
    } 
    boggleDictionary = dictionary;
    humansScore = 0;
}

/**
 * @brief Boggle::getCurrentBoard
 * Returns string of letters on the Boggle board. For use in setting
 * up the initial boggle gui board.
 * @return - string of letters on the Boggle board.
 */
string Boggle::getCurrentBoard() {
    return board;
}

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
char Boggle::getLetter(int row, int col) {
    try {
        if (row >= sqrt(BOARD_SIZE) || col >= sqrt(BOARD_SIZE)) error("out of bounds");
        return board[(row * 4) + col];
    } catch (ErrorException& error) {
        return ' '; // empty character
    }
}

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
bool Boggle::checkWord(string word) {
    if (word.length() < 4 || 
        !boggleDictionary.contains(word) ||
        humanWords.contains(word)) return false;
    return true;
}

/**
 * @brief Boggle::humanWordSearch
 * @param word
 * @return 
 */
bool Boggle::humanWordSearch(string word) {
    if(!checkWord(word)) return false;
    
    BoggleGUI::clearHighlighting();
    chosenHumanSquares.clear();
    if(!recursiveHumanSearch(toUpperCase(word), -1)) return false;
    
    // add word to score and used words set
    humansScore += word.length() - 3;
    humanWords.add(word);
    return true;   // remove this
}

/**
 * @brief Boggle::recursiveHumanSearch
 * @param word
 * @param currIndex
 * @return 
 */
bool Boggle::recursiveHumanSearch(string word, int currIndex) {
    if (word.length() == 0) return true;
    
    for (int possibleIndex : availableSquares(currIndex)) {
        cout << "checking " << possibleIndex << " from currIndex of " << currIndex << endl;
        BoggleGUI::setHighlighted(possibleIndex / 4, possibleIndex % 4, true);
        BoggleGUI::setAnimationDelay(100);
        if (board[possibleIndex] == word[0]) {
            currIndex = possibleIndex;
            chosenHumanSquares.add(currIndex);
            if (recursiveHumanSearch(word.substr(1, string::npos), currIndex)) return true;
            // unmake
            chosenHumanSquares.remove(currIndex); 
            BoggleGUI::setHighlighted(possibleIndex / 4, possibleIndex % 4, false);
        }
        BoggleGUI::setHighlighted(possibleIndex / 4, possibleIndex % 4, false);
    }
    
    return false;
}

/**
 * @brief Boggle::availableSquares
 * @param currIndex
 * @return 
 */
Vector<int> Boggle::availableSquares(int currIndex) {
    Vector<int> availableSquares;
    
    if (currIndex == -1) { // first layer of recursion, return all squares
        for (int i = 0; i < 16; i++) {
            availableSquares.add(i);
        }
    } else { // return all in-bounds and unchosen neighboring squares
        int numRows = sqrt(BOARD_SIZE);
        int currRow = currIndex % 4;
        int currCol = currIndex / 4; 
        
        for (int i = max(0, currRow - 1); i <= min(numRows - 1, currRow + 1); i++) { // row
            for (int j = max(0, currCol - 1); j <= min(numRows - 1, currCol + 1); j++) { // column
                int neighborIndex = i + j * 4;
                if (neighborIndex == currIndex) continue; // don't check the square itself
                if (chosenHumanSquares.contains(neighborIndex)) continue; // don't check squares that have already been marked
                availableSquares.add(neighborIndex);
            } 
        }
    }
    
    return availableSquares;
}

/**
 * @brief Boggle::humanScore
 * @return 
 */
int Boggle::humanScore() {
    return humansScore;
}

/**
 * @brief Boggle::getNumHumanWords
 * @return 
 */
int Boggle::getNumHumanWords() {
    return humanWords.size();
}

/**
 * @brief Boggle::getHumanWords
 * @return 
 */
string Boggle::getHumanWords() {
    return humanWords.toString();
}

Set<string> Boggle::computerWordSearch() {
    // TODO: implement
    Set<string> result;   // remove this
    return result;        // remove this
}

int Boggle::getScoreComputer() {
    // TODO: implement
    return 0;   // remove this
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    return out;
}
