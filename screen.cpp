/*
    Implementation of the Screen class
    by Kathy Yuen

    Description: This file contains all function definitions of all
    the functions declared in the header file.
*/

#include <cstdlib>
#include <vector>
#include <iostream>
#include <time.h>
#include "screen.hpp"

/*
    This is the default constructor for the Screen. It creates and displays the
    screen based on user inputted variables for rows and columns.
*/
Screen::Screen(int r, int c) {
    // create board
    row = r;
    column = c;
    int cellCounter = 0;

    for (int i = 0; i < row + 2; i++) {
        // create the board
        // -1 means that the cell is either a border or occupied
        std::vector<int> boardRow(column + 2, -1);
        board.push_back(boardRow);
        
        // make all the cells that are not the border free cells
        if (i != 0 && i != row + 1) {
            for (int j = 1; j <= column; j++) {
                Cell c;
                c.row = i;
                c.column = j;
                makeFree(c);
            }
        }
    }
}

/*
    This function takes in a Cell as an argument and puts it into the
    freeCells vector and saves the index of the given cell onto the
    board.
*/
void Screen::makeFree(Cell c) {
    freeCells.push_back(c);
    board[c.row][c.column] = freeCells.size() - 1;
}

/*
    This function takes in a Cell argument and marks the given cell as
    occupied. The cell is removed from the freeCells vector by taking
    the last cell in the freeCells vector and replacing Cell c.
    The index for the last cell is updated on the board.
*/
void Screen::wormOccupy(Cell c) {
    int index = board[c.row][c.column];

    // go to cell location and mark it as occupied
    board[c.row][c.column] = -1;

    // remove cell from freeCells
    freeCells[index] = freeCells[freeCells.size() - 1];
    freeCells.pop_back();

    // update cell index on board
    Cell movedCell = freeCells[index];
    board[movedCell.row][movedCell.column] = index;
}

/* 
    This function accepts a cell and returns true if it is not
    occupied, false if it is.
*/
bool Screen::isFree(Cell c) {
    return board[c.row][c.column] != -1;
}

/* This function returns a random Cell from freeCells. */
Cell Screen::getRandomFreeCell() {
    srand(time(0));
    int randomCellIndex = rand() % freeCells.size();
    return freeCells[randomCellIndex];
}