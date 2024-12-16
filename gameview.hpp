/*
    GameView header file
    by Kathy Yuen

    Description: The GameView class uses curses to create the game
    board on the terminal. This class allows the user to play an
    interactive worm game that keeps track of the user's score.
*/

#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include "screen.hpp"

const int SEC_DELAY = 0;
const int USEC_DELAY = 800000;
static char lastc = ' ';
enum Direction { UP = 'w', DOWN = 's', LEFT = 'a', RIGHT = 'd' };

class GameView {
    public:
        GameView(int boardRow, int boardColumn); // default constructor

        // Reads in a character from the keyboard
        char get_char();
        void die();

        // Creates screen with curses
        void startup();
        // Ends screen 
        void terminate();
        // Draws the Worm game borders
        void drawScreen(Screen &wormGame, Worm &boardWorm);
        // Places the worm onto the board
        void placeWorm(Screen &wormGame, Worm &boardWorm);
        // Places a snack onto the board
        void placeSnack(Screen &wormGame);
        // Allows user to play the game
        void playGame(Screen &wormGame, Worm &boardWorm);

    private:
        int row, column;
        int score;
        int snack;
        Cell snackCell;
};

#endif