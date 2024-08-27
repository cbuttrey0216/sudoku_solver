#ifndef SUDOKUGRID_H
#define SUDOKUGRID_H
#include <string>
using namespace std;

class SudokuGrid {
private:
    int** grid;
    static const int SIZE = 9;

public:
    SudokuGrid(const string&);
    ~SudokuGrid();

    void readFromFile(const string&);
    bool checkValidation(int, int, int);
    bool solve(int, int);
    void printSudokuGrid();
};

#endif