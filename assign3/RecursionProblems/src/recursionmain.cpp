/*
 * CS 106B Recursion Problems
 * This client program contains a text menu for running your
 * assignment's various recursion problems.
 * You don't need to modify this file.
 */

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "gevents.h"
#include "ginteractors.h"
#include "gobjects.h"
#include "grid.h"
#include "gwindow.h"
#include "map.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
#include "recursionproblems.h"
using namespace std;

// constants for min/max weight in human pyramid
const int MIN_WEIGHT = 50;
const int MAX_WEIGHT = 150;

// uncomment the line below to 'rig' the random number generator
// for the Human Pyramid problem
#define HUMAN_PYRAMID_RANDOM_SEED 106

// constants for graphical window sizes
const int SIERPINSKI_WINDOW_WIDTH = 700;
const int SIERPINSKI_WINDOW_HEIGHT = 450;
const int SIERPINSKI_FIGURE_SIZE = 400;
const int FLOOD_WINDOW_WIDTH = 500;
const int FLOOD_WINDOW_HEIGHT = 400;
const int FLOOD_FILL_NUM_SHAPES = 100;

// uncomment the line below to get the same shapes every time for flood fill
#define FLOOD_FILL_RANDOM_SEED 42

// private globals to help implement flood fill pixel functionality
static Grid<int> floodFillPixels;
static GWindow* floodFillWindow;

int main() {
    cout << "CS 106B Recursion Problems" << endl;
    while (true) {
        cout << endl;
        cout << "Choose a problem:" << endl;
        cout << "1) Karel Goes Home" << endl;
        cout << "2) Convert String to Integer" << endl;
        cout << "3) Balancing Parentheses" << endl;
        cout << "4) Human Pyramid" << endl;
        cout << "5) Sierpinski Triangle" << endl;
        cout << "6) Flood Fill" << endl;
        cout << "7) Grammar Solver" << endl;
        int choice = getInteger("Enter your choice (or 0 to quit): ");
        cout << endl;
        if (choice == 0)      { break; }
        else if (choice == 1) { test_karelGoesHome(); }
        else if (choice == 2) { test_convertStringToInteger(); }
        else if (choice == 3) { test_balancingParentheses(); }
        else if (choice == 4) { test_humanPyramid(); }
        else if (choice == 5) { test_sierpinskiTriangle(); }
        else if (choice == 6) { test_floodFill(); }
        else if (choice == 7) { test_grammarSolver(); }
    }

    cout << "Exiting." << endl;
    return 0;
}

/*
 * This function runs and tests your countKarelPaths function.
 * Prints a grid of various street/avenue locations and their numbers of paths.
 */
void test_karelGoesHome() {
    const int GRID_SIZE = 10;
    const int FIELD_WIDTH = 7;

    cout << "Karel's path count for several possible locations:" << endl;
    for (int street = GRID_SIZE; street > 0; street--) {
        for (int avenue = 1; avenue <= GRID_SIZE; avenue++) {
            int nPaths = countKarelPaths(street, avenue);
            cout << right << setw(FIELD_WIDTH) << setfill(' ') << nPaths;
        }
        cout << endl;
    }
}

/*
 * This function runs and tests your convertStringToInteger function.
 * Prompts for a string and then reports its integer equivalent.
 */
void test_convertStringToInteger() {
    while (true) {
        cout << "Enter a string representing an integer (or Q to quit): ";
        string exp = toLowerCase(trim(getLine()));
        if (exp == "q") {
            break;
        }

        bool valid = !exp.empty();
        for (int i = 0; i < (int) exp.length(); i++) {
            if (!isdigit(exp[i]) && exp[i] != '-') {
                cout << "That is not a valid integer string." << endl;
                cout << "Your string should not contain the character '"
                     << exp[i] << "'." << endl;
                valid = false;
                break;
            }
        }

        if (valid) {
            int converted = convertStringToInteger(exp);
            cout << "string \"" << exp << "\" converted into int "
                 << dec << converted << endl;
        }
    }
}

/*
 * This function runs and tests your isBalanced function.
 * Prompts for a string and then reports whether it is balanced.
 */
void test_balancingParentheses() {
    while (true) {
        cout << "Enter a string (or Q to quit): ";
        string exp = toLowerCase(getLine());
        if (exp == "q") {
            break;
        }
        if (isBalanced(exp)) {
            cout << "Yes, that string is balanced!" << endl;
        } else {
            cout << "No, that string is not balanced." << endl;
        }
    }
}


/*
 * Runs and tests your humanPyramid function.
 */
void test_humanPyramid() {
    int cols = getInteger("How many people are on the bottom row? ");

    // possibly rig the random generator's output
#ifdef HUMAN_PYRAMID_RANDOM_SEED
    setRandomSeed(HUMAN_PYRAMID_RANDOM_SEED);
#endif // HUMAN_PYRAMID_RANDOM_SEED

    // populate vector of weights
    Vector<Vector<double> > weights;
    for (int row = 0; row < cols; row++) {
        Vector<double> currentRow;
        for (int col = 0; col <= row; col++) {
            double weight = randomReal(MIN_WEIGHT, MAX_WEIGHT);
            currentRow.add(weight);
        }
        weights.add(currentRow);
    }

    // print weights
    cout << "Each person's own weight:" << endl;
    cout << fixed << setprecision(2);
    for (int row = 0; row < weights.size(); row++) {
        for (int col = 0; col < weights[row].size(); col++) {
            cout << weights[row][col] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // print weight on knees for each person in pyramid
    cout << "Weight on each person's knees:" << endl;
    for (int row = 0; row < weights.size(); row++) {
        for (int col = 0; col < weights[row].size(); col++) {
            double result = weightOnKnees(row, col, weights);
            cout << result << " ";
        }
        cout << endl;
    }
    cout << resetiosflags(ios::fixed | ios::floatfield);
}

/*
 * Runs and tests your drawSierpinskiTriangle function.
 * Prompts the user for the fractal's order, then displays it.
 */
void test_sierpinskiTriangle() {
    int order = getInteger("Fractal order? ");
    GWindow gw(SIERPINSKI_WINDOW_WIDTH, SIERPINSKI_WINDOW_HEIGHT);
    gw.setWindowTitle("CS 106B Sierpinski Triangle");
    // gw.setExitOnClose(true);
    // gw.center();
    int x0 = (SIERPINSKI_WINDOW_WIDTH - SIERPINSKI_FIGURE_SIZE) / 2;
    int y0 = 20;

    drawSierpinskiTriangle(gw, x0, y0, SIERPINSKI_FIGURE_SIZE, order);
}

/*
 * Runs and tests your floodFill function.
 */
void test_floodFill() {
    GObject::setAntiAliasing(false);
    floodFillWindow = new GWindow(FLOOD_WINDOW_WIDTH, FLOOD_WINDOW_HEIGHT);
    floodFillWindow->setWindowTitle("CS 106B Flood Fill");
    // floodFillWindow->center();
    // floodFillWindow->setRepaintImmediately(false);

    Map<string, int> colorMap;
    colorMap["Red"]    = 0x8c1515;   // Stanford red
    colorMap["Yellow"] = 0xeeee00;   // yellow
    colorMap["Blue"]   = 0x0000cc;   // blue
    colorMap["Green"]  = 0x00cc00;   // green
    colorMap["Purple"] = 0xcc00cc;   // purple
    colorMap["Orange"] = 0xff8800;   // orange
    Vector<string> colorVector = colorMap.keys();

    GLabel* fillLabel = new GLabel("Fill color:");
    GChooser* colorList = new GChooser();
    for (string key : colorMap) {
        colorList->addItem(key);
    }
    floodFillWindow->addToRegion(fillLabel, "SOUTH");
    floodFillWindow->addToRegion(colorList, "SOUTH");

    // draw several random shapes
#ifdef FLOOD_FILL_RANDOM_SEED
    setRandomSeed(FLOOD_FILL_RANDOM_SEED);
#endif // FLOOD_FILL_RANDOM_SEED

    for (int i = 0; i < FLOOD_FILL_NUM_SHAPES; i++) {
        double x = randomInteger(0, FLOOD_WINDOW_WIDTH  - 100);
        double y = randomInteger(0, FLOOD_WINDOW_HEIGHT - 100);
        double w = randomInteger(20, 100);
        double h = randomInteger(20, 100);
        int color = colorMap[colorVector[randomInteger(0, colorVector.size() - 1)]];
        GRect* gobj = new GRect(x, y, w, h);
        gobj->setColor(color);
        gobj->setFilled(true);
        gobj->setFillColor(color);
        floodFillWindow->add(gobj);
    }

    // fill allPixels grid with the color of every pixel
    floodFillPixels.resize(FLOOD_WINDOW_WIDTH, FLOOD_WINDOW_HEIGHT);
    for (int y = 0; y < FLOOD_WINDOW_HEIGHT; y++) {
        for (int x = 0; x < FLOOD_WINDOW_WIDTH; x++) {
            GObject* obj = floodFillWindow->getGObjectAt(x, y);
            if (obj == NULL) {
                floodFillPixels[x][y] = 0xffffff;   // white
            } else {
                floodFillPixels[x][y] = convertColorToRGB(obj->getColor());
            }
        }
    }

    // main event loop to process events as they happen
    while (true) {
        GEvent e = waitForEvent(MOUSE_EVENT | WINDOW_EVENT);
        if (e.getEventClass() == MOUSE_EVENT) {
            if (e.getEventType() != MOUSE_CLICKED) { continue; }
            colorList->setEnabled(false);
            GMouseEvent mouseEvent(e);
            string colorStr = colorList->getSelectedItem();
            int color = colorMap[colorStr];
            int mx = (int) mouseEvent.getX();
            int my = (int) mouseEvent.getY();
            cout << "Flood fill at (x=" << dec << mx << ", y=" << my << ")"
                 << " with color " << hex << setw(6) << setfill('0') << color
                 << dec << endl;
            floodFill(mx, my,
                      FLOOD_WINDOW_WIDTH, FLOOD_WINDOW_HEIGHT,
                      color);
            colorList->setEnabled(true);
            // floodFillWindow->repaint();
        } else if (e.getEventClass() == WINDOW_EVENT) {
            if (e.getEventType() == WINDOW_CLOSED) {
                // make sure that it was the flood fill window that got closed
                if (!floodFillWindow->isOpen() || !floodFillWindow->isVisible()) {
                    break;
                }
            }
        }
    }
    cout << resetiosflags(ios::fixed | ios::floatfield);
}

/*
 * Returns the color of the given x/y pixel onscreen.
 * If the x/y coordinates are out of range, throws an Error.
 */
int getPixelColor(int x, int y) {
    if (!floodFillPixels.inBounds(x, y)) {
        ostringstream out;
        out << "getPixelColor: (x=" << x
            << ", y=" << y << ") is out of bounds";
        error(out.str());
    }
    return floodFillPixels[x][y];
}

/*
 * Sets the color of the given x/y pixel onscreen to the given color.
 * If the x/y coordinates or color are out of range, throws an Error.
 */
void setPixelColor(int x, int y, int color) {
    if (!floodFillPixels.inBounds(x, y)) {
        ostringstream out;
        out << "setPixelColor: (x=" << x
            << ", y=" << y << ") is out of bounds";
        error(out.str());
    }
    if (color < 0 || color > 0xffffff) {
        ostringstream out;
        out << "setPixelColor: color of " << hex << color
            << " is out of range";
        error(out.str());
    }

    floodFillPixels[x][y] = color;
    GRect* rect = new GRect(x, y, 1, 1);
    rect->setColor(color);
    rect->setFillColor(color);
    floodFillWindow->add(rect);
}

/*
 * Runs and tests your grammarGenerate function.
 * Prompts for the input file and symbol, then calls your function.
 */
void test_grammarSolver() {
    ifstream input;
    promptUserForFile(input, "Grammar file name? ");
    while (true) {
        string symbol = trim(getLine("Symbol to generate (Enter to quit)? "));
        if (symbol.empty()) {
            break;
        }

        int times = getInteger("How many to generate? ");
        rewindStream(input);
        cout << endl;
        Vector<string> result = grammarGenerate(input, symbol, times);
        for (int i = 0; i < result.size(); i++) {
            cout << setw(2) << (i+1) << ": " << result[i] << endl;
        }
        cout << endl;
    }
}
