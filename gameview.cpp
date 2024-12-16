/*
    Implementation of the GameView class
    by Kathy Yuen

    Description: This file contains all the implementations of 
    the GameView class functions declared in the header file.
*/

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sgtty.h>
#include <curses.h>
#include <signal.h>
#include "gameview.hpp"

/*
    The default constructor has parameters for the row and column
    size of the board and initializes all private variables.
*/
GameView::GameView(int boardRow, int boardColumn) {
    row = boardRow;
    column = boardColumn;
    score = 0;
    snack = 0;
    snackCell.row = 0;
    snackCell.column = 0;
}

/*
    This function reads in a character and only returns the defined
    up, down, left, and right (WASD) characters or a space if nothing or 
    something else is typed on the keyboard.
*/
char GameView::get_char() {
    char c;
    struct timeval tvec;
    fd_set rfds;

    tvec.tv_sec = SEC_DELAY;
    tvec.tv_usec = USEC_DELAY;
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    int retval = select(1, &rfds, NULL, NULL, &tvec);

    if (retval < 0)
        die();
    
    if (retval) {
        if (read(0, &c, 1) < 0)
            die();

        if (c == UP || c == DOWN || c == LEFT || c == RIGHT) {
            lastc = c;
        }
        else {
            lastc = ' ';
        }
    }
    return(lastc);
}

/* Used in the get_char function. */
void GameView::die() {
    signal(SIGINT, SIG_IGN);
    mvcur(0, COLS - 1, LINES - 1, 0);
    endwin();
    exit(1);
}

/* Prepares the screen for the game. */
void GameView::startup() {
    initscr();	    /* activate the curses */
    curs_set(0);    /* do not display the cursor */
    clear();	    /* clear the screen that curses provides */
    noecho();	    /* prevent the input chars to be echoed to the screen */
    cbreak();	    /* change the stty so that characters are delivered to the
		            program as they are typed--no need to hit the return key!*/
}

/* Ends the game screen and returns back to the terminal. */
void GameView::terminate() {
    mvcur( 0, COLS - 1, LINES - 1, 0 );
    clear();
    refresh();
    endwin();
}

/*
    Draws the initial screen of the worm game with user specified values.
    The title of the game is in the top left and the score of the user
    is kept in the top right corner. The worm is placed in the middle of 
    the board.
*/
void GameView::drawScreen(Screen &wormGame, Worm &boardWorm) {
    startup();
    move(0, 0);
    addstr("Worm");
    move(0, wormGame.column - 5);
    addstr("Score 0");

    // create screen border
    for (int screenRow = 0; screenRow < wormGame.row + 2; screenRow++) {
        for (int screenCol  = 0; screenCol < wormGame.column + 2; screenCol++) {
            if (screenRow == 0 || screenRow == wormGame.row + 1) {
                move(screenRow + 1, screenCol);
                addstr("*");
            }
            else {
                if (screenCol == 0 || screenCol == wormGame.column + 1) {
                    move(screenRow + 1, screenCol);
                    addstr("*");
                }
            }
        }
    }

    // place worm and snack
    placeWorm(wormGame, boardWorm);
    placeSnack(wormGame);
    refresh();
}

/* The inital worm is created and placed onto the board. */
void GameView::placeWorm(Screen &wormGame, Worm &boardWorm) {
    Cell wormStartCell;
    wormStartCell.row = row / 2;
    wormStartCell.column = column / 2 - 3;
    
    for (int i = 0; i < 8; i ++) {
        boardWorm.addHead(wormStartCell);
        wormGame.wormOccupy(wormStartCell);
        wormStartCell.column++;
    }

    move(row / 2 + 1, column / 2 - 3);
    addstr("ooooooo@");
}

/*
    A random empty cell is chosen and a snack value is displayed on
    the screen.
*/
void GameView::placeSnack(Screen &wormGame) {
    snackCell = wormGame.getRandomFreeCell();
    srand(time(0));
    snack = rand() % 9 + 1;

    // print snack on screen
    move(snackCell.row + 1, snackCell.column);
    addstr(std::to_string(snack).c_str());
}

/*
    The user controls how the worm moves with their inputs
    that are being read by this function. The game keeps track of 
    the user's score and grows the worm according to the snack
    value that is eaten by the worm. The worm dies when it runs
    into itself or the borders of the game.
*/
void GameView::playGame(Screen &wormGame, Worm &boardWorm) {
    char c;
    bool dead = false;
    Cell newHead = boardWorm.head();

    while (!dead) {
        c = get_char();
        if (c == UP) newHead.row--;
        else if (c == DOWN) newHead.row++;
        else if (c == LEFT) newHead.column--;
        else if (c == RIGHT) newHead.column++;
        else continue;
        
        // check if worm ran into occupied cell
        if (!wormGame.isFree(newHead)) {
            dead = true;
            continue;
        }

        // update worm visually on board
        mvaddch(newHead.row + 1, newHead.column, '@');
        mvaddch(boardWorm.head().row + 1, boardWorm.head().column, 'o');
        boardWorm.addHead(newHead);
        wormGame.wormOccupy(newHead);

        // if worm ate snack, update score and create new snack
        if (newHead.row == snackCell.row && newHead.column == snackCell.column) {
            score += snack;
            mvaddstr(0, wormGame.column + 1, std::to_string(score).c_str());
            placeSnack(wormGame);
        }

        // remove tail if snack wasn't eaten
        if (boardWorm.wormSize - 9 == score) {
            mvaddch(boardWorm.tail().row + 1, boardWorm.tail().column, ' ');
            wormGame.makeFree(boardWorm.tail());
            boardWorm.removeTail();
        }
        refresh();
    }
    terminate();
    std::cout << "The worm died since it ran into something!" << std::endl;
    std::cout << "Your final score was: " << score << std::endl;
}