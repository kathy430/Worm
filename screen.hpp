/*
    Screen class header file
    by Kathy Yuen

    Description: The Screen class creates the board for the worm game.
    The screen is made up of cells and each cell location is labeled by
    its index in the freeCells vector. If a cell on the board is not free,
    it is labeled with a -1.
*/

#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <vector>
#include "worm.hpp"

class Screen {
    public:
        Screen(int r, int c); // default constructor

        // Make c a free (empty) cell
        void makeFree(Cell c);
        // Mark cell c as occupied
        void wormOccupy(Cell c);
        // Return true if c is free, false if it's occupied
        bool isFree(Cell c);
        // Randomly select and return a free cell to place the snack in
        Cell getRandomFreeCell();

        

    public:
        int row;
        int column;
        std::vector<Cell> freeCells;
        std::vector<std::vector<int>> board;
        friend class GameView;
        
};

#endif