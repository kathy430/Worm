/*
    Worm header file
    by Kathy Yuen

    Description: A worm is created and handled by a circular queue.
    The circular queue is made up of Cells that the worm is occupying
    on the game board.
*/

#ifndef WORM_HPP
#define WORM_HPP

struct Cell {
    int row, column;
};

class Worm {
    public:
        Worm(int row, int column); // default constructor
        Worm(const Worm& other); // copy constructor
        ~Worm(); // destructor

        // Given a cell, make it the new heaad of the worm
        void addHead(Cell c);
        // Remove the worm's tail from the queue
        void removeTail();
        // Return the cell representing the position of the worm's head without modifying the worm
        Cell head();
        // Return the cell representing the position of the worm's tail without modifying the worm
        Cell tail();

    private:
        Cell* worm;
        int maxWormSize;
        int headIndex, tailIndex;
        int wormSize;
        friend class GameView;
};

#endif