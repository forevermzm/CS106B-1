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
using namespace std;

void drawTriangle(GWindow& gw, int x, int y, int sideLength);
string complement(string str);
void fill(int x, int y, int width, int height, int color, int startColor);
int stringToInt(string exp);
int charToInt(string number);

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
    // TODO: write this function
    Vector<string> v;
    return v;
}
