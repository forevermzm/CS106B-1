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

int countKarelPaths(int street, int avenue) {    
    if (street == 1 && avenue == 1) return 1; // reached the end square, valid path
    if (street < 1 || avenue < 1) return 0; // hit outer bounds of world, invalid path
    return countKarelPaths(street - 1, avenue) + countKarelPaths(street, avenue - 1);
    
    // can't use -- because can't alter original values of street and avenue
}

int convertStringToInteger(string exp) {
    if (exp.length() <= 0) return 0;
}

bool isBalanced(string exp) {
    // TODO: write this function
    return false;
}

double weightOnKnees(int row, int col, Vector<Vector<double> >& weights) {
    // TODO: write this function
    return 0.0;
}

void drawSierpinskiTriangle(GWindow& gw, int x, int y, int size, int order) {
    // TODO: write this function

}

void floodFill(int x, int y, int width, int height, int color) {
    // TODO: write this function

}

Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    // TODO: write this function
    Vector<string> v;
    return v;
}
