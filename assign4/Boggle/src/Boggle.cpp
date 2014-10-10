// .cpp file of Boggle class. Implements functions that keep track
// of data from the two players of a game and searches the board
// for particular words for both players.

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
    computersScore = 0;
}


string Boggle::getCurrentBoard() {
    return board;
}

char Boggle::getLetter(int row, int col) {
    try {
        if (row >= sqrt(BOARD_SIZE) || col >= sqrt(BOARD_SIZE)) error("out of bounds");
        return board[(row * 4) + col];
    } catch (ErrorException& error) {
        return ' '; // empty character
    }
}

bool Boggle::checkWord(string word) {
    return (word.length() >= 4 
            && boggleDictionary.contains(word) 
            && !humanWords.contains(word));
}


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

bool Boggle::findWordOnBoard(string word, int currIndex) {
    if (word.length() == 0) return true;
    
    // for all possible squares based on the current square's location - 
    for (int possibleIndex : availableSquares(currIndex)) {
        if (possibleIndex >= 16) continue; // out of bounds, skip checking this square
                
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

Vector<int> Boggle::availableSquares(int currIndex) {
    Vector<int> availableSquares;
    
    if (currIndex == -1) { // first layer of recursion, return all squares
        for (int i = 0; i < 17; i++) { // returns one out of bounds square as marker to computer search that it is done
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
    Set<string> result; 
    findAllWordsOnBoard(result, -1, "");
    return result - humanWords;      
}

bool Boggle::findAllWordsOnBoard(Set<string>& foundWords, int currIndex, string currWord) {
    for (int possibleIndex : availableSquares(currIndex)) {
        if (possibleIndex == 16) return true; // end of the board
        
        // make the choice
        currWord += board[possibleIndex];
        chosenComputerSquares.add(possibleIndex);
        
        // it's an actual word!
        if (boggleDictionary.contains(currWord) && currWord.length() >= 4) { 
            foundWords.add(currWord);
            BoggleGUI::recordWord(currWord, BoggleGUI::COMPUTER);
            computersScore += currWord.length() - 3;
        }
        
        // keep searching but good start; can be applied to existing word prefixes
        if (boggleDictionary.containsPrefix(currWord)) { 
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
    return computersScore - humansScore;
}

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
