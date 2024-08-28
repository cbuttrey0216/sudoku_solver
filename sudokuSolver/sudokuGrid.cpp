#include "SudokuGrid.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//
//  Contructor
//
SudokuGrid::SudokuGrid(const string& fileName) {  

    // Dynamically allocates an array of arrays  
    grid = new int*[SIZE];
    for(int i = 0; i < SIZE; i++) {
        grid[i] = new int[SIZE];
    }

    readFromFile(fileName);
}


//
//  Destructor
//
SudokuGrid::~SudokuGrid() {
    //deletes SudokuGrid
    for(int i = 0; i < SIZE; i++) {
        delete[] grid[i];
    }
    delete[] grid;
}


//
//  Reads the sudoku from a file
//
void SudokuGrid::readFromFile(const string& fileName) {
    ifstream inFile;
    inFile.open(fileName);
    
    if(!inFile.is_open()) {
        throw runtime_error("File failed to open.");
    }

    string line;
    int row = 0;

    // Read the file line by line
    while (getline(inFile, line) && row < SIZE) {
        stringstream ss(line);
        string token;
        int column = 0;

        // Extract integers separated by '#'
        while (getline(ss, token, '#') && column < SIZE) {
            try {
                grid[row][column] = stoi(token);
            } catch (const invalid_argument& e) {
                throw runtime_error("Invalid integer in file at line " + to_string(row + 1) + ", column " + to_string(column + 1));
            }
            column++;
        }

        if (column != SIZE) {
            throw runtime_error("Incorrect number of columns at line " + to_string(row + 1));
        }

        row++;
    }

    if (row != SIZE) {
        throw runtime_error("Incorrect number of rows in file.");
    }

    inFile.close();
}


//
//  Checks if number is valid to input
//
bool SudokuGrid::checkValidation(int r, int c, int insertedNum){

    // checks to see if the number is the row or the column
    for(int i = 0; i < SIZE; i++) {
        if(grid[r][i] == insertedNum || grid[i][c] == insertedNum)
            return false;
    }

    // finds the leftmost and rightmost of a 3x3 grid
    int boxRowStart = (r / 3) * 3;
    int boxColStart = (c / 3) * 3;

    // checks every box in it's respective 3x3 grid
    for(int i = boxRowStart; i < boxRowStart + 3; i++) {
        for(int j = boxColStart; j < boxColStart + 3; j++) {
            if(grid[i][j] == insertedNum) {
                return false;
            }
        }
    }

    return true;
}


//
//  Solves the SudokuGrid
//
bool SudokuGrid::solve(int r = 0, int c = 0) {
    if(r == SIZE) 
        { return true; }
    else if(c == SIZE)
        { return solve(r+1, 0); }
    else if(grid[r][c] != 0)
        { return solve(r, c+1); }
    else {
        for(int i = 1; i <= SIZE; i++) {
            if(checkValidation(r, c, i)) {
                grid[r][c] = i;
                if(solve(r, c+1))
                    { return true; }
                grid[r][c] = 0;
            }
        }
        return false;
    }   
}


//
//  Prints the SudokuGrid
//
void SudokuGrid::printSudokuGrid() {
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}