#pragma once
// Controller class
#include <curses.h>
#include <time.h>
#include <stdlib.h>
#include "Board.h"
#include "Drawable.h"
#include "Growth.h"
#include "Empty.h"
#include "TitleScreen.h"
#include "Snake.h"

class SnakeGame 
{
    Board board;
    Growth* growth;
    bool game_over;
    TitleScreen title;
    Snake snake;
public:
    SnakeGame(int height, int width) :growth(NULL)
    {
        title.titleOn();
        title.titleOff();
        board = Board(height, width);
        initialize();
    }
    ~SnakeGame()
    {
        delete growth;
    }
    void initialize()
    {

        board.initialize();
        game_over = false;
        srand(time(NULL));

        snake.setDirection(down);
        SnakePiece next = SnakePiece(11, 11);
        board.add(next);
        snake.addPiece(next);

        next = snake.nextHead();
        board.add(next);
        snake.addPiece(next);
        
        next = snake.nextHead();
        board.add(next);
        snake.addPiece(next);
        snake.setDirection(right);

        next = snake.nextHead();
        board.add(next);
        snake.addPiece(next);
    }
    void processInput()
    {
        chtype input = board.getInput();
        switch (input)
        {
        case KEY_UP:
        case 'w':
            snake.setDirection(up);
            break;
        case KEY_DOWN:
        case 's':
            snake.setDirection(down);
            break;
        case KEY_LEFT:
        case 'a':
            snake.setDirection(left);
            break;
        case KEY_RIGHT:
        case 'd':
            snake.setDirection(right);
            break;
        default:
            break;
        }
    }

    void updateState()
    {
        int y, x;
        if (growth == NULL) {
            board.getEmptyCoordinates(y, x);
            growth = new Growth(y, x);
            board.add(*growth);
            board.add(Empty(growth->getY(), growth->getX()));
        }
        SnakePiece next = snake.nextHead();
        if (next.getX() != growth->getX() && next.getY() != growth->getY())
        {
            int emptyRow = snake.tail().getY();
            int emptyCol = snake.tail().getX();
            board.add(Empty(emptyRow, emptyCol));
            snake.removePiece();
        }
        board.add(next);
        snake.addPiece(next);
    }

    void redraw()
    {
    }

    bool isOver()
    {
        return game_over;
    }

};