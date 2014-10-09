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
    return (word.length() >= 4 
            && boggleDictionary.contains(word) 
            && !humanWords.contains(word));
}

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
bool Boggle::humanWordSearch(string word) {
    // if word isn't worth checking, don't look
    if(!checkWord(word)) return false;
    
    // empty chosen human squares set
    chosenHumanSquares.clear();
    
    // if word isn't on the board, return false
    if(!findWordOnBoard(toUpperCase(word), -1)) return false;
    
    // otherwise, word is good so add word to score and used words set
    chosenHumanSquares.clear();
    humansScore += word.length() - 3;
    humanWords.add(toUpperCase(word));
    return true;
}

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
bool Boggle::findWordOnBoard(string word, int currIndex) {
    if (word.length() == 0) return true;
    
    // for all possible squares based on the current square's location - 
    for (int possibleIndex : availableSquares(currIndex)) {
        // highlight letters on GUI
        BoggleGUI::setHighlighted(possibleIndex / 4, possibleIndex % 4, true);
        BoggleGUI::setAnimationDelay(100);
        
        // if the current square's letter matches the first letter of the search word, proceed
        if (board[possibleIndex] == word[0]) {
            // make the choice
            currIndex = possibleIndex;
            chosenHumanSquares.add(currIndex);
            // try solving from here
            if (findWordOnBoard(word.substr(1, string::npos), currIndex)) return true;
            // didn't work out, so unmake the choice
            chosenHumanSquares.remove(currIndex); 
            BoggleGUI::setHighlighted(possibleIndex / 4, possibleIndex % 4, false);
        }
        BoggleGUI::setHighlighted(possibleIndex / 4, possibleIndex % 4, false);
    }
    
    return false;
}

/**
 * @brief Boggle::availableSquares
 * Returns a vector of all the neighboring square indexes based on the current
 * location on the board.
 * @param currIndex - Current location on the board. If -1, then searching has not
 * started yet, so return the indexes of the entire board.
 * @return - Vector of neighboring squares' indexes
 */
Vector<int> Boggle::availableSquares(int currIndex) {
    Vector<int> availableSquares;
    
    if (currIndex == -1) { // first layer of recursion, return all squares
        for (int i = 0; i < 17; i++) {
            availableSquares.add(i);
        }
    } else { // return all in-bounds and unchosen neighboring squares
        int numRows = sqrt(BOARD_SIZE);
        int currRow = currIndex % 4;
        int currCol = currIndex / 4; 
        
        for (int i = max(0, currRow - 1); i <= min(numRows - 1, currRow + 1); i++) { // row
            for (int j = max(0, currCol - 1); j <= min(numRows - 1, currCol + 1); j++) { // column
                int neighborIndex = i + j * 4;
                if (neighborIndex == currIndex) continue;      // don't check the square itself
                if (chosenHumanSquares.contains(neighborIndex) // don't check squares that have already been marked
                        || chosenComputerSquares.contains(neighborIndex)) continue; 
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
    Set<string> result; 
    
    findAllWordsOnBoard(result, -1, "");
    return result;      
}

bool Boggle::findAllWordsOnBoard(Set<string>& foundWords, int currIndex, string currWord) {
    for (int possibleIndex : availableSquares(currIndex)) {
        if (possibleIndex == 16) return true;
        
//        cout << "[" << currIndex << "] " << currWord << ": checking " << board[possibleIndex] << " from " << board[currIndex] << endl;
//        cout << "BLAH" << endl;
//        cout << chosenComputerSquares << endl;
        
        // make the choice
        currWord += board[possibleIndex];
        chosenComputerSquares.add(possibleIndex);
        
        if (boggleDictionary.contains(currWord) && currWord.length() >= 4) { // it's an actual word!
            cout << currWord << " is a real word!" << endl;
            foundWords.add(currWord);
            currIndex = possibleIndex;
            findAllWordsOnBoard(foundWords, currIndex, currWord);
        } else if (boggleDictionary.containsPrefix(currWord)) { // keep searching but good start
//            cout << currWord << " is a valid prefix!" << endl;
            currIndex = possibleIndex;
            findAllWordsOnBoard(foundWords, currIndex, currWord);
        }
        
        // unmake choice
        currWord = currWord.substr(0, currWord.length()-1);
        chosenComputerSquares.remove(possibleIndex);
    }
    return false;
}

int Boggle::getScoreComputer() {
    // TODO: implement
    return 0;   // remove this
}

/**
 * @brief operator <<
 * Prints board in 4x4 format when cout-ed to the console.
 * @param out
 * @param boggle
 * @return 
 */
ostream& operator<<(ostream& out, Boggle& boggle) {
    int rows = sqrt(Boggle::BOARD_SIZE);
    int cols = rows;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            out << boggle.getLetter(i, j);
        }
        out << endl;
    }
    return out;
}
