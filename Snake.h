#pragma once
#include "Drawable.h"
#include <queue>
#define SNAKE_BODY '+'
#define SNAKE_HEAD '&'
enum Direction
{
    up, // 0
    down, // 1
    left, // 2
    right // 3
};
// 스네이크 한부분도 그릴수 있는 것(좌표와 아이콘을 갖는)
class SnakePiece : public Drawable 
{
public:
    SnakePiece() 
    {
        this->y = this->x = 0;
        this->icon = SNAKE_BODY;
    }
    SnakePiece(int y, int x) 
    {
        this->y = y;
        this->x = x;
        this->icon = SNAKE_BODY;
    }
};
// 스네이크는 큐로 표현됨.
class Snake
{
    std::queue<SnakePiece> pieces;
    Direction cur_direction;
public:
    Snake()
    {
        cur_direction = down;
    }

    /*void changeHead(char ch)
    {
        if (!pieces.empty())
        {
            pieces.back().getIcon() = '0';
        }
    }*/
    void addPiece(SnakePiece piece)
    {
        pieces.push(piece);
    }

    void removePiece()
    {
        pieces.pop();
    }

    SnakePiece tail()
    {
        return pieces.front();
    }

    SnakePiece head()
    {
        return pieces.back();
    }

    Direction getDirection()
    {
        return cur_direction;
    }

    void setDirection(Direction d)
    {

        cur_direction = d;
    }
    
    SnakePiece nextHead()
    {
        int row = head().getY();
        int col = head().getX();
        switch (cur_direction)
        {
        case up:
            row--;
            break;
        case down:
            row++;
            break;
        case left:
            col--;
            break;
        case right:
            col++;
            break;
        default:
            break;
        }
        return SnakePiece(row, col);
    }
};