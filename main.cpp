/*
    Project 2 Worm game main file
    by Kathy Yuen
    
    Description: This is the main file that combines all header files
    and runs the game. It reads in a command line input from the user 
    and checks to make sure that the rows given is 9-25 (inclusive) and 
    the columns given is 9-80 (inclusive). The game ends when the worm
    runs into itself or the border of the game. The user can move the worm
    with WASD keys.
*/
#include <iostream>
#include <string>
#include "gameview.hpp"
#include "screen.hpp"
#include "worm.hpp"

int main(int argc, char* argv[]) {
    // read in game borders
    int row, column;
    row = std::stoi(argv[1]);
    column = std::stoi(argv[2]);

    // check row is 9 - 25(inclusive), column is 9-80 (inclusive)
    if (row < 9 || row > 25) {
        std::cerr << "Row value is not between 9-25 (inclusive)" << std::endl;
        exit(1);
    }
    if (column < 9 || column > 80) {
        std::cerr << "Column value is not between 9-80 (inclusive)" << std::endl;
        exit(1);
    }
    
    // play the game
    Worm worm(row, column);
    Screen scren(row, column);
    GameView game(row, column);
    game.drawScreen(scren, worm);
    game.playGame(scren, worm);

    return 0;
}