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
void createGrid(ifstream &stream, Grid<char> &grid);
void nextGeneration(Grid<char> &grid);
int min(int check, int min);
int max(int check, int max);

int main() {
    printWelcomeMessage();

    ifstream stream;
    promptForFile(stream);

    Grid<char> grid(0, 0);
    createGrid(stream, grid);

    nextGeneration(grid);

    cout << "Have a nice Life!" << endl;
    return 0;
}

void printWelcomeMessage() {
    cout << "Welcome to the CS 106B Game of Life," << '\n'
         << "a simulation of the lifecycle of a bacteria colony." << '\n'
         << "Cells (X) live and die by the following rules:" << '\n'
         << "- A cell with 1 or fewer neighbors dies." << '\n'
         << "- Locations with 2 neighbors remain stable." << '\n'
         << "- Locations with 3 neighbors will create life." << '\n'
         << "- A cell with 4 or more neighbors dies." << endl;
}

/*
 * Prompt user for file until proper file is given.
 */
void promptForFile(ifstream &stream) {
    string filename = "";

    while(true) {
        filename = promptUserForFile(stream, "Grid input file name? ");
        if (fileExists(filename)) break;
    }
}

void createGrid(ifstream &stream, Grid<char> &grid) {
    string line;

    getline(stream, line);
    int rows = stringToInteger(line);

    getline(stream, line);
    int columns = stringToInteger(line);

    grid.resize(rows, columns);

    for (int i = 0; i < rows; i++) {
        getline(stream, line);
        for (int j = 0; j < columns; j++) {
            grid[i][j] = line[j];
        }
    }
}

void nextGeneration(Grid<char> &grid) {
    // create temporary grid copy
    Grid<char> tempGrid(grid.numRows(), grid.numCols());

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
