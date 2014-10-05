// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Boggle.h"
#include <cmath>
#include "error.h"

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

bool Boggle::humanWordSearch(string word) {
    if (!checkWord(word)) return false;
    // TODO: implement
    
    humansScore += word.length() - 3;
    humanWords.add(word);
    return true;   // remove this
}

int Boggle::humanScore() {
    return humansScore;
}

int Boggle::getNumHumanWords() {
    return humanWords.size();
}

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
