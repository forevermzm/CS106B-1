/*
 * CS106B Homework 1, Game of Life
 * Claire Huang
 */

// libraries
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "random.h"
#include "lifegui.h"

using namespace std;

typedef struct {
    ifstream stream;
    Grid<char> grid;
    Grid<char> tempGrid;
    LifeGUI gui;
} GameContext;

// function prototypes
void printWelcomeMessage();
void promptForFile(GameContext &context);
void createGrid(GameContext &context);
void createRandomGrid(GameContext &context);
char getRandomCell();
void nextGeneration(GameContext &context);
int min(int check, int min);
int max(int check, int max);
bool menu(GameContext &context);

int main() {
    printWelcomeMessage();

    GameContext context;

    promptForFile(context);

    while (menu(context)); // continue playing game until user asks to quit

    cout << "Have a nice Life!";
    return 0;
}

/*
 * Prints welcome message and rules of the game.
 */
void printWelcomeMessage() {
    cout << "Welcome to the CS 106B Game of Life," << '\n'
         << "a simulation of the lifecycle of a bacteria colony." << '\n'
         << "Cells (X) live and die by the following rules:" << '\n'
         << "- A cell with 1 or fewer neighbors dies." << '\n'
         << "- Locations with 2 neighbors remain stable." << '\n'
         << "- Locations with 3 neighbors will create life." << '\n'
         << "- A cell with 4 or more neighbors dies." << endl << endl;
}

/*
 * Prompts user for file until proper file is given.
 */
void promptForFile(GameContext &context) {
    string filename = "";

    while(true) {
        filename = getLine("Grid input file name (or \"random\")? ");
        if (filename == "random") {
            createRandomGrid(context);
            break;
        } else if (fileExists(filename)) {
            openFile(context.stream, filename);
            createGrid(context);
            break;
        }
    }
}

/*
 * Reads input file from user, and creates and fills in
 * two grids (one temporary). Prints out the initial state
 * of the grid.
 */
void createGrid(GameContext &context) {
    string line;

    // get size of grid
    getline(context.stream, line);
    int rows = stringToInteger(line);

    getline(context.stream, line);
    int columns = stringToInteger(line);

    // resize grid and gui
    context.grid.resize(rows, columns);
    context.tempGrid.resize(rows, columns);
    context.gui.resize(rows, columns);

    // fill in cells of grid
    for (int i = 0; i < rows; i++) {
        getline(context.stream, line);
        for (int j = 0; j < columns; j++) {
            context.grid[i][j] = line[j];
            context.gui.drawCell(i, j, (context.grid[i][j] == 'X'));
        }
    }
}

/*
 * If user inputs "random" as filename, creates a grid
 * of random size and with random cells. Prints out initial
 * state of grid.
 */
void createRandomGrid(GameContext &context) {
    // get size of grid
    int rows = randomInteger(1, 50);
    int columns = randomInteger(1, 50);

    // resize grid and gui
    context.grid.resize(rows, columns);
    context.tempGrid.resize(rows, columns);
    context.gui.resize(rows, columns);

    // fill in cells of grid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            context.grid[i][j] = getRandomCell();
            context.gui.drawCell(i, j, (context.grid[i][j] == 'X'));
        }
    }
}

char getRandomCell() {
    if (randomChance(.5)) {
        return 'X';
    } else {
        return '-';
    }
}

/*
 * Advances the grid one generation and prints out new state
 * of the cells. For each cell in the grid, it counts how
 * many neighbors there are, updates the temporary grid
 * accordingly, and then copies the temporary grid over
 * to the original.
 */
void nextGeneration(GameContext &context) {
    // for each cell:
    for (int row = 0; row < context.grid.numRows(); row++) {
        for (int col = 0; col < context.grid.numCols(); col++) {
            // count number of living neighbors
            int neighborsCount = 0;

            for (int i = max(row - 1, 0); i <= min(row + 1, context.grid.numRows() - 1); i++) {
                for (int j = max(col - 1, 0); j <= min(col + 1, context.grid.numCols() - 1); j++) {
                    if (i == row && j == col) continue; // don't check the cell itself
                    if (context.grid[i][j] == 'X') {
                        neighborsCount++;
                    }
                }
            }

            // change in temporary
            switch (neighborsCount) {
                case 0: case 1:
                    context.tempGrid[row][col] = '-';
                    break;
                case 2:
                    context.tempGrid[row][col] = context.grid[row][col];
                    break;
                case 3:
                    context.tempGrid[row][col] = 'X';
                    break;
                default:
                    context.tempGrid[row][col] = '-';
                    break;
            }

            context.gui.drawCell(row, col, (context.tempGrid[row][col] == 'X'));
        }
    }
    // copy temporary back over to original grid
    context.grid = context.tempGrid;
}

/*
 * Returns the larger of two integer parameters.
 * Used for keeping the grid indexes in bounds.
 */
int max(int check, int max) {
    if (check < max) {
        return max;
    } else {
        return check;
    }
}

/*
 * Returns the smaller of two integer parameters.
 * Used for keeping the grid indexes in bounds.
 */
int min(int check, int min) {
    if (check > min) {
        return min;
    } else {
        return check;
    }
}

/*
 * Prompts user for the next action and returns boolean
 * for whether or not the game should continue.
 */
bool menu(GameContext &context) {
    string input;

    // reprompt for valid input
    while(true) {
        input = getLine("a)nimate, t)ick, q)uit? ");
        if (input == "a" || input == "t" || input == "q") break;
        cout << "Invalid choice; please try again." << endl;
    }

    // do appropriate action and return whether main should continue execution
    if (input == "a") { // animate
        int numFrames = getInteger("How many frames? ");
        for (int i = 0; i < numFrames; i++) {
            clearConsole();
            nextGeneration(context);
            pause(50);
        }
        return true;
    } else if (input == "t") { // tick
        nextGeneration(context);
        return true;
    } else if (input == "q") { // quit
        return false;
    } else {
        return true;
    }
}
