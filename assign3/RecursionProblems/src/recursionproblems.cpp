#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "gwindow.h"
#include "hashmap.h"
#include "map.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
#include "recursionproblems.h"
#include "set.h"
using namespace std;

void drawTriangle(GWindow& gw, int x, int y, int sideLength);
string complement(string str);
void fill(int x, int y, int width, int height, int color, int startColor);
int stringToInt(string exp);
int charToInt(string number);
bool isBalancedRecursive(string exp, Stack<string> &openedBrackets);
bool isOpenBracket(string bracket);
bool isClosedBracket(string bracket);
bool matchesOpenedBracket(string bracket, Stack<string> &openedBrackets);
bool readFile(istream& input, Map<string, Vector<string> >& grammarRules);
string generateSentence(string symbol, Map<string, Vector<string> >& grammarRules, string& result);

/**
 * @brief countKarelPaths
 * Counts number of paths Karel can take from any square back to the 
 * bottom left corner if Karel only moves down and left.
 * @param street
 * @param avenue
 * @return 
 */
int countKarelPaths(int street, int avenue) {    
    if (street == 1 && avenue == 1) return 1; // reached the end square, valid path
    if (street < 1 || avenue < 1) return 0; // hit outer bounds of world, invalid path
    return countKarelPaths(street - 1, avenue) + countKarelPaths(street, avenue - 1);
    
    // can't use street-- because can't alter original values of street and avenue
}

/**
 * @brief convertStringToInteger
 * Wrapper function that determines whether the inputted number is positive or
 * negative and multiplies the result of the recursive function stringToInt
 * by 1 or -1.
 * @param exp
 * @return 
 */
int convertStringToInteger(string exp) {
    if (exp[0] == '-') {
        return -1 * stringToInt(exp);
    } else {
        return stringToInt(exp);
    }
}

/**
 * @brief stringToInt
 * @param exp
 * @return 
 */
int stringToInt(string exp) {
    if (exp.length() == 1 && exp == "-") return 0; // don't want to deal with the dash
    if (exp.length() == 1) return charToInt(exp); // base case: 
    
    string substrFront = exp.substr(0, exp.size() - 1);
    string substrEnd = exp.substr(exp.size() - 1, 1);
    int total = 10 * stringToInt(substrFront) + charToInt(substrEnd);
        
    return total;
}

/**
 * @brief charToInt
 * Helper function that converts a one-character string into an int.
 * @param number
 * @return 
 */
int charToInt(string number) {
    const char* ch = number.c_str();
    return (ch[0] - '0');
}

/**
 * @brief isBalanced
 * Checks if, in the inputted string, each ([{ has a pair.
 * APPROACH #1: find first occurence of matching pair, remove the pair,
 *              and check if the remaining string is balanced.
 *              PROBLEM: doesn't check for nested-ness. ([)] is acceptable
 * APPROACH #2: find last occurence of matching pair and check if the string
 *              inside the pair is balanced and if the string to the right of
 *              the closing pair is balanced.
 *              PROBLEM: ()() doesn't work b/c looks at last ) so checks for )(
 *                       which isn't balanced.
 * APPROACH #3: use stack to store all open brackets in order and check them against
 *              closing brackets in order -- fully solves nested problems.
 * @param exp
 * @return 
 */
bool isBalanced(string exp) {
    Stack<string> openedBrackets;
    return isBalancedRecursive(exp, openedBrackets);
}

bool isBalancedRecursive(string exp, Stack<string> &openedBrackets) {
    // empty string is always balanced as long as there are no opened brackets left hanging
    if (exp.length() == 0 && openedBrackets.isEmpty()) return true; 
    
    string firstBracket = exp.substr(0, 1);
    
    if (isOpenBracket(firstBracket)) {
        openedBrackets.push(firstBracket);
        return isBalancedRecursive(exp.substr(1), openedBrackets);
    } else if (isClosedBracket(firstBracket)) {
        return matchesOpenedBracket(firstBracket, openedBrackets) 
                && isBalancedRecursive(exp.substr(1), openedBrackets);
    } else {
        return false;
    }
}

bool isOpenBracket(string bracket) {
    return (bracket == "(" || bracket == "[" || bracket == "{");
}

bool isClosedBracket(string bracket) {
    return (bracket == ")" || bracket == "]" || bracket == "}");
}

/**
 * @brief matchesOpenedBracket
 * Checks if inputted closed bracket matches the last open bracket
 * in the string. If there are no more open brackets, returns false 
 * because the inputted closed bracket is extra and doesn't have a pair.
 * @param bracket
 * @param openedBrackets
 * @return 
 */
bool matchesOpenedBracket(string bracket, Stack<string> &openedBrackets) {
    if(openedBrackets.isEmpty()) return false;
    return (complement(openedBrackets.pop()) == bracket);
}

/**
 * @brief complement
 * Returns closing complement of a given opening bracket.
 * @param str
 * @return 
 */
string complement(string str) {
    if (str == "(") {
        return ")";
    } else if (str == "[") {
        return "]";
    } else if (str == "{") {
        return "}";
    } else {
        return "-"; // won't ever appear in the input string
    }
}

/**
 * @brief weightOnKnees
 * Calculates weight on knees of each person in a pyramid of people 
 * with their randomly generated weights.
 * @param row
 * @param col
 * @param weights
 * @return 
 */
double weightOnKnees(int row, int col, Vector<Vector<double> >& weights) {
    // out of bounds
    if (row < 0 || row >= weights.size() || col < 0 || col >= weights[row].size()) return 0.0;
    
    if (row == 0 && col == 0) return weights[row][col];
    
    return weights[row][col] 
            + 0.5 * weightOnKnees(row - 1, col - 1, weights) 
            + 0.5 * weightOnKnees(row - 1, col, weights);
}

/**
 * @brief drawSierpinskiTriangle
 * Draws Sierpinski triangle of specified order.
 * @param gw
 * @param x
 * @param y
 * @param size
 * @param order
 */
void drawSierpinskiTriangle(GWindow& gw, int x, int y, int size, int order) {
    if (order == 1) {
        drawTriangle(gw, x, y, size);
        return;
    }
    
    drawSierpinskiTriangle(gw, x, y, size / 2, order - 1);              // left
    drawSierpinskiTriangle(gw, x + (size / 2), y, size / 2, order - 1); // right
    drawSierpinskiTriangle(gw, x + (size / 4), y + (sqrt(3) / 2) * (size / 2), // bottom
                           size / 2, order - 1);
}

/**
 * @brief drawTriangle
 * Helper function that draws triangle of specified dimensions.
 * @param gw
 * @param x
 * @param y
 * @param sideLength
 */
void drawTriangle(GWindow& gw, int x, int y, int sideLength) {
    int height = y + (sqrt(3) / 2) * sideLength;
    gw.drawLine(x, y, x + 0.5*sideLength, height);              // left side
    gw.drawLine(x, y, x + sideLength, y);                       // top side
    gw.drawLine(x + sideLength, y, x + 0.5*sideLength, height); // right side
}

/**
 * @brief floodFill
 * Wrapper function that remembers original color and passes it 
 * into recursive function.
 * @param x
 * @param y
 * @param width
 * @param height
 * @param color
 */
void floodFill(int x, int y, int width, int height, int color) {
    int startColor = getPixelColor(x, y);
    fill(x, y, width, height, color, startColor);
}

/**
 * @brief fill
 * Fills an area of the same color with a different color.
 * @param x
 * @param y
 * @param width
 * @param height
 * @param color
 * @param startColor
 */
void fill(int x, int y, int width, int height, int color, int startColor) {
    if (x < 0 || x > width-1 || y < 0 || y > height-1) return; // looking out of bounds
    if (getPixelColor(x, y) == color) return; // same color as fill color
    if (getPixelColor(x, y) != startColor) return; // reached outside of color blob
    
    setPixelColor(x, y, color);
    fill(x-1, y, width, height, color, startColor);
    fill(x+1, y, width, height, color, startColor);
    fill(x, y-1, width, height, color, startColor);
    fill(x, y+1, width, height, color, startColor);
}

/**
 * @brief grammarGenerate
 * Generates sentences or expressions based on inputted grammar rules file.
 * @param input
 * @param symbol
 * @param times
 * @return 
 */
Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    Vector<string> v;
    Map<string, Vector<string> > grammarRules;
    
    // checking for valid input
    if (times <= 0) {
        return v;
    }
    if (symbol.empty()) {
        cout << "Symbol cannot be empty." << endl;
        return v;
    }
    if (!readFile(input, grammarRules)) {
        cout << "Grammar file contains more than 1 rule for the same symbol.";
        return v;
    }
    
    for (int i = 0; i < times; i++) {
        string result;
        generateSentence(symbol,grammarRules, result);
        v.add(result);
    }
    
    return v;
}

/**
 * @brief readFile
 * Reads file and stores grammar rules in map of string keys (non-terminals)
 * and vector of possible non/terminals.
 * @param input
 * @param grammarRules
 * @return 
 */
bool readFile(istream& input, Map<string, Vector<string> >& grammarRules) {
    string line, key;
    Vector<string> value;
    Set<string> usedNonTerminals;
    
    while(true) {
        // empty variables for reuse
        line = "";
        key = "";
        value.clear();
        
        // get line
        getline(input, line);
        if (input.fail()) break; // end of file
        trim(line);
        
        // get key and value
        key = line.substr(0, line.find("::="));
        if (usedNonTerminals.contains(key)) return false;
        usedNonTerminals.add(key);
        value = stringSplit(line.substr(key.length()+3, string::npos), "|");
        
        // put into map
        grammarRules.put(key, value);
    }
    
    return true;
}

/**
 * @brief generateSentence
 * Given a symbol, generates a phrase of terminals and returns it.
 * @param symbol
 * @param grammarRules
 * @param result
 * @return 
 */
string generateSentence(string symbol, Map<string, Vector<string> >& grammarRules, string& result) {
    if (!grammarRules.containsKey(symbol)) return symbol + " "; // terminal
    
    Vector<string> rules = grammarRules.get(symbol);
    string randomRule = rules.get(randomInteger(0, rules.size() - 1));
    trim(randomRule);
    Vector<string> tokens = stringSplit(randomRule, " ");
    
    for (string token : tokens) {
        result += generateSentence(token, grammarRules, result);
    }
    
    return "";
}
