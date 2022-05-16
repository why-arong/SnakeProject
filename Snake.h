#pragma once
#include "Drawable.h"
#include <queue>

enum Direction
{
    up,
    down,
    left,
    right
};
class SnakePiece : public Drawable 
{
public:
    SnakePiece() 
    {
        this->y = this->x = 0;
        this->icon = '#';
    }
    SnakePiece(int y, int x) 
    {
        this->y = y;
        this->x = x;
        this->icon = '#';
    }
};

class Snake
{
    std::queue<SnakePiece> pieces;
    Direction cur_direction;
public:
    Snake()
    {
        cur_direction = right;
    }

    void addPiece(SnakePiece piece)
    {
        pieces.push(piece);
    }

    void removePiece(SnakePiece piece)
    {
        pieces.pop();
    }

    SnakePiece tail()
    {
        return pieces.back();
    }

    SnakePiece head()
    {
        return pieces.front();
    }

};