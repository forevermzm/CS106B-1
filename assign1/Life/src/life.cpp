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
#include "lifegui.h"
using namespace std;

void printWelcomeMessage();
void promptForFile(ifstream &stream);
void createGrid(ifstream &stream);
void nextGeneration();
int min(int check, int min);
int max(int check, int max);
bool menu();

// NOTE: ASSIGNMENT SAYS "DO NOT DECLARE ANY GLOBAL VARIABLES"
Grid<char> grid(0, 0);
Grid<char> tempGrid(0,0);

int main() {
    printWelcomeMessage();

    ifstream stream;
    promptForFile(stream);

    createGrid(stream);

    while (menu());

    cout << "Have a nice Life!";
    return 0;
}

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
void promptForFile(ifstream &stream) {
    string filename = "";

    while(true) {
        filename = promptUserForFile(stream, "Grid input file name? ");
        if (fileExists(filename)) break;
    }
}

void createGrid(ifstream &stream) {
    string line;

    getline(stream, line);
    int rows = stringToInteger(line);

    getline(stream, line);
    int columns = stringToInteger(line);

    grid.resize(rows, columns);
    tempGrid.resize(rows, columns);

    for (int i = 0; i < rows; i++) {
        getline(stream, line);
        for (int j = 0; j < columns; j++) {
            grid[i][j] = line[j];
            cout << grid[i][j];
        }
        cout << endl;
    }
}

void nextGeneration() {
    // for each cell:
    for (int row = 0; row < grid.numRows(); row++) {
        for (int col = 0; col < grid.numCols(); col++) {
            // count number of living neighbors
            int neighborsCount = 0;

            for (int i = max(row - 1, 0); i <= min(row + 1, grid.numRows() - 1); i++) {
                for (int j = max(col - 1, 0); j <= min(col + 1, grid.numCols() - 1); j++) {
                    if (i == row && j == col) continue; // don't check the cell itself
                    if (grid[i][j] == 'X') {
                        neighborsCount++;
                    }
                }
            }

            // change in temporary
            switch (neighborsCount) {
                case 0: case 1:
                    tempGrid[row][col] = '-';
                    break;
                case 2:
                    tempGrid[row][col] = grid[row][col];
                    break;
                case 3:
                    tempGrid[row][col] = 'X';
                    break;
                default:
                    tempGrid[row][col] = '-';
                    break;
            }

            cout << tempGrid[row][col];
        }
        cout << endl;
    }
    // copy temporary back over to original grid
    grid = tempGrid;
}

int max(int check, int max) {
    if (check < max) {
        return max;
    } else {
        return check;
    }
}

int min(int check, int min) {
    if (check > min) {
        return min;
    } else {
        return check;
    }
}

bool menu() {
    char input;

    // reprompt for valid input
    while(true) {
        cout << "a)nimate, t)ick, q)uit? ";
        cin >> input;
        if (input == 'a' || input == 't' || input == 'q') break;
        cout << "Invalid choice; please try again." << endl;
    }

    // do appropriate action and return whether main should continue execution
    switch(input) {
        case 'a': // animate
        {
            int numFrames = getInteger("How many frames? ");
            for (int i = 0; i < numFrames; i++) {
                clearConsole();
                nextGeneration();
                pause(50);
            }
            return true;
        }
        case 't': // tick
            nextGeneration();
            return true;
        case 'q': // quit
            return false;
        default:
            return true;
    }
}
