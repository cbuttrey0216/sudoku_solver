#include "SudokuGrid.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    // create a SudokuGrid w/ text file name
    // call readFromFile 
    // print

    SudokuGrid sudoku("sudoku.txt");
    cout << "\nUnsolved grid:\n";
    sudoku.printSudokuGrid();
    cout << "\n\nSolving...";
    if (sudoku.solve(0, 0)) {
        cout << "\nSudoku solved successfully:" << endl;
        sudoku.printSudokuGrid();
    } else {
        cout << "Failed to solve Sudoku." << endl;
    }
    
    return 0;
}
