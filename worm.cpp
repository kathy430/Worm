/*
    Implementation of the Worm class
    by Kathy Yuen

    Description: All of the declared functions of the worm class
    are implemented below.
*/

#include <iostream>
#include "worm.hpp"

/*
    This constructor accepts a row and column argument to produce a circular queue
    for the worm that is in the middle of the board.
*/
Worm::Worm(int row, int column) {
    // generate circular array with max worm size
    maxWormSize = row * column;
    worm = new Cell[maxWormSize];
    tailIndex = headIndex = 0;
}

/*
    The copy constructor that copies one worm object from the other.
    The copy constructor only copies the the cells of the worm that 
    are currently a part of the worm.
*/
Worm::Worm(const Worm& other) {
    int size = sizeof(other.worm);
    // create new worm and only copy cells of the current worm over
    worm = new Cell[size];
    int otherTailIndex = other.tailIndex;
    for (int i = 0; i < other.wormSize; i++) {
        // see if we reached end of the circle queue
        if (otherTailIndex == size) {
            // loop to the beginning if we're at end
            otherTailIndex = 0;
        }
        worm[i] = other.worm[otherTailIndex];
        otherTailIndex++;
    }
    tailIndex = 0;
    headIndex = other.wormSize - 1;
}

/* The worm destructor deletes the circular worm array. */
Worm::~Worm() {
    delete worm;
}

/*
    This function accepts a cell argument and makes it the worm's head.
    Worm size is incremented afterwards.
*/
void Worm::addHead(Cell c) {
    // check if worm is empty or if we are at end of circular queue
    if (wormSize == 0 || headIndex == maxWormSize - 1) {
        worm[0] = c;
        headIndex = 0;
    }
    else {
        worm[headIndex + 1] = c;
        headIndex++;
    }
    wormSize++;
}

/*
    This function removes the worm's current tail by shifting it to the 
    next cell. Worm size is decremented afterwards.    
*/
void Worm::removeTail() {
    // check if we are at end of circular queue
    if (tailIndex == maxWormSize - 1) {
        // at the end, move to beginning of the queue
        tailIndex = 0;
    }
    else {
        // not at the end
        tailIndex++;
    }
    wormSize--;
}

/* Return the cell representing the position of the worm's head. */
Cell Worm::head() {
    return worm[headIndex];
}

/* Return the cell representing the position of the worm's tail. */
Cell Worm::tail() {
    return worm[tailIndex];
}