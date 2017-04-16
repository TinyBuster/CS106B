/*
 * Assignment 1 of stanford CS106B
 * -------------------------------
 * This program simulates the generation of cells in
 * this computer world! Given an initial pattern,
 * the game simulates the birth and death of future
 * generations of cells using a set of simple rules.
 */

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
#include "strlib.h"
#include "lifegui.h"
using namespace std;

void printInstruction();
void play();
void printGrid(Grid<char> &grid);
Grid<char> nextGeneration_N(Grid<char> &grid);
Grid<char> nextGeneration_Y(Grid<char> &grid);

int main() {
    printInstruction();
    play() ;

    cout << "Have a nice Life!" << endl;
    return 0;
}


// prints the instruction to the console.
void printInstruction() {
    cout << "Welcome to the CS 106B Game of Life," << endl;
    cout << "a simulation of the lifecycle of a bacteria colony." << endl;
    cout << "Cells (X) live and die by the following rules:" << endl;
    cout << "- A cell with 1 or fewer neighbors dies." << endl;
    cout << "- Locations with 2 neighbors remain stable." << endl;
    cout << "- Locations with 3 neighbors will create life." << endl;
    cout << "- A cell with 4 or more neighbors dies." << endl << endl;
}

// simulates the birth and death of future generations of cells
void play() {

    //asks the user for a filename, which includes the data for the game.
    ifstream infile;
    while(true) {
        string filename = getLine("Grid input file name?");
        if(fileExists(filename)) {
            openFile(infile, filename);
            break;
        } else {
            cout << "Unable to open that file.  Try again." << endl;
        }
    }

    // asks user to decide the way to simulate the game
    string ch;
    while (true) {
        ch = getLine("Should the simulation wrap around the grid (y/n)? ");
        if (ch == "y" || ch == "n" || ch == "Y" || ch == "N") break;
        cout << "Invalid choice; please try again." << endl;
    }

    // reads the data from the file to a grid
    string line;
    getline(infile, line);
    int nrow = stringToInteger(line);
    getline(infile, line);
    int ncolumn = stringToInteger(line);
    LifeGUI game;
    game.resize(nrow, ncolumn);

    Grid<char> bacteria(nrow, ncolumn);
    for (int i = 0; i < nrow; i++) {
        getline(infile, line);
        for (int j = 0; j < ncolumn; j++) {
            bacteria[i][j] = line[j];
        }
    }
    printGrid(bacteria);

    for (int i = 0; i < nrow; i++) {
        for (int j = 0; j < ncolumn; j++) {
            game.drawCell(i, j, bacteria[i][j] == 'X');
        }
    }

    // asks the user for what to do, animate, tick or quit the game.
    while (true) {
        string decision = getLine("a)nimate, t)ick, q)uit? ");
        int frame;
        if (decision == "q" || decision == "Q") {
            break;
        } else if (decision == "a" || decision == "A") {
            while (true) {
                frame = getInteger("How many frames? ");
                if (frame > 0) break;
                cout << "Illegal integer format. Try again." << endl;
            }
            for(int i = 0; i < frame; i++) {
                Grid<char> next(nrow, ncolumn);
                if (ch == "y" || ch == "Y") {
                    next = nextGeneration_Y(bacteria);
                } else if (ch == "n" || ch == "N") {
                    next = nextGeneration_N(bacteria);
                }
                clearConsole();
                printGrid(next);

                for (int i = 0; i < nrow; i++) {
                    for (int j = 0; j < ncolumn; j++) {
                        game.drawCell(i, j, next[i][j] == 'X');
                    }
                }

                bacteria = next;
                pause(50);
            }
        } else if (decision == "t" || decision == "T") {
            Grid<char> next(nrow, ncolumn);
            if (ch == "y" || ch == "Y") {
                next = nextGeneration_Y(bacteria);
            } else if (ch == "n" || ch == "N") {
                next = nextGeneration_N(bacteria);
            }
            printGrid(next);

            for (int i = 0; i < nrow; i++) {
                for (int j = 0; j < ncolumn; j++) {
                    game.drawCell(i, j, next[i][j] == 'X');
                }
            }

            bacteria = next;
        } else {
            cout << "Invalid choice; please try again." << endl;
        }
    }
    infile.close();
}

// prints the current generation
void printGrid(Grid<char> &grid) {
    int row = grid.nRows;
    int column = grid.nCols;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}


// simulates the next generation under the condition of unwrapping
Grid<char> nextGeneration_N(Grid<char> &grid) {
    Grid<char> tempt(grid.nRows, grid.nCols);

    for (int i = 0; i < grid.nRows; i++) {
        for (int j = 0; j < grid.nCols; j++) {
            int neighbors = 0;
            if (grid.inBounds(i-1,j-1)) {
                if (grid[i-1][j-1] == 'X')
                    neighbors++;
            }
            if (grid.inBounds(i-1,j)) {
                if (grid[i-1][j] == 'X')
                    neighbors++;
            }
            if (grid.inBounds(i-1,j+1)) {
                if (grid[i-1][j+1] == 'X')
                    neighbors++;
            }
            if (grid.inBounds(i,j-1)) {
                if (grid[i][j-1] == 'X')
                    neighbors++;
            }
            if (grid.inBounds(i,j+1)) {
                if (grid[i][j+1] == 'X')
                    neighbors++;
            }
            if (grid.inBounds(i+1,j-1)) {
                if (grid[i+1][j-1] == 'X')
                    neighbors++;
            }
            if (grid.inBounds(i+1,j)) {
                if (grid[i+1][j] == 'X')
                    neighbors++;
            }
            if (grid.inBounds(i+1,j+1)) {
                if (grid[i+1][j+1] == 'X')
                    neighbors++;
            }
            if (neighbors <= 1) {
                tempt[i][j] = '-';
            } else if (neighbors == 2) {
                tempt[i][j] = grid[i][j];
            } else if (neighbors == 3) {
                tempt[i][j] = 'X';
            } else {
                tempt[i][j] = '-';
            }
        }
    }
    return tempt;
}

// simulates the next generation under the condition of wrapping
Grid<char> nextGeneration_Y(Grid<char> &grid) {
    Grid<char> tempt(grid.nRows, grid.nCols);

    for (int i = 0; i < grid.nRows; i++) {
        for (int j = 0; j < grid.nCols; j++) {
            int neighbors = 0;
            if (grid[(i-1+grid.nRows)%grid.nRows][(j-1+grid.nCols)%grid.nCols] == 'X')
                neighbors++;
            if (grid[(i-1+grid.nRows)%grid.nRows][(j+grid.nCols)%grid.nCols] == 'X')
                neighbors++;
            if (grid[(i-1+grid.nRows)%grid.nRows][(j+1+grid.nCols)%grid.nCols] == 'X')
                neighbors++;
            if (grid[(i+grid.nRows)%grid.nRows][(j-1+grid.nCols)%grid.nCols] == 'X')
                neighbors++;
            if (grid[(i+grid.nRows)%grid.nRows][(j+1+grid.nCols)%grid.nCols] == 'X')
                neighbors++;
            if (grid[(i+1+grid.nRows)%grid.nRows][(j-1+grid.nCols)%grid.nCols] == 'X')
                neighbors++;
            if (grid[(i+1+grid.nRows)%grid.nRows][(j+grid.nCols)%grid.nCols] == 'X')
                neighbors++;
            if (grid[(i+1+grid.nRows)%grid.nRows][(j+1+grid.nCols)%grid.nCols] == 'X')
                neighbors++;

            if (neighbors <= 1) {
                tempt[i][j] = '-';
            } else if (neighbors == 2) {
                tempt[i][j] = grid[i][j];
            } else if (neighbors == 3) {
                tempt[i][j] = 'X';
            } else {
                tempt[i][j] = '-';
            }
        }
    }
    return tempt;
}
