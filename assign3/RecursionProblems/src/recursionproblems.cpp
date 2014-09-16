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
bool readFile(istream& input, Map<string, Vector<string> >& grammarRules);
string generateSentence(string symbol, Map<string, Vector<string> >& grammarRules, string& result);

int countKarelPaths(int street, int avenue) {    
    if (street == 1 && avenue == 1) return 1; // reached the end square, valid path
    if (street < 1 || avenue < 1) return 0; // hit outer bounds of world, invalid path
    return countKarelPaths(street - 1, avenue) + countKarelPaths(street, avenue - 1);
    
    // can't use street-- because can't alter original values of street and avenue
}

int convertStringToInteger(string exp) {
    if (exp[0] == '-') {
        return -1 * stringToInt(exp);
    } else {
        return stringToInt(exp);
    }
}

int stringToInt(string exp) {
    if (exp.length() == 1 && exp == "-") return 0;
    if (exp.length() == 1) return charToInt(exp);
    
    string substrFront = exp.substr(0, exp.size() - 1);
    string substrEnd = exp.substr(exp.size() - 1, 1);
    int total = 10 * stringToInt(substrFront) + charToInt(substrEnd);
        
    return total;
}

int charToInt(string number) {
    const char* ch = number.c_str();
    return (ch[0] - '0');
}

bool isBalanced(string exp) {
    if (exp.length() == 0) return true; // empty string is always balanced
    
    int foundIndex = exp.substr(1, string::npos).find(complement(exp.substr(0, 1))); // find the pair of the first character
    if (foundIndex == string::npos) {
        return false;
    } else {
        string newString = exp.substr(1, string::npos).replace(foundIndex, 1, ""); // remove pair
        return isBalanced(newString);
    }
    
    return false;
}

string complement(string str) {
    if (str == "(") {
        return ")";
    } else if (str == "[") {
        return "]";
    } else if (str == "{") {
        return "}";
    } else {
        return "";
    }
}

double weightOnKnees(int row, int col, Vector<Vector<double> >& weights) {
    // out of bounds
    if (row < 0 || row >= weights.size() || col < 0 || col >= weights[row].size()) return 0.0;
    
    if (row == 0 && col == 0) return weights[row][col];
    
    return weights[row][col] 
            + 0.5 * weightOnKnees(row - 1, col - 1, weights) 
            + 0.5 * weightOnKnees(row - 1, col, weights);
}

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

void drawTriangle(GWindow& gw, int x, int y, int sideLength) {
    int height = y + (sqrt(3) / 2) * sideLength;
    gw.drawLine(x, y, x + 0.5*sideLength, height);              // left side
    gw.drawLine(x, y, x + sideLength, y);                       // top side
    gw.drawLine(x + sideLength, y, x + 0.5*sideLength, height); // right side
}

void floodFill(int x, int y, int width, int height, int color) {
    int startColor = getPixelColor(x, y);
    fill(x, y, width, height, color, startColor);
}

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
