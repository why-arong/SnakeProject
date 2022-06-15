#pragma once
#include "Drawable.h"
#include <queue>
#define SNAKE_BODY 'B'
#define SNAKE_HEAD 'H'
enum Direction
{
    up, // 0
    down, // 1
    left, // 2
    right // 3
};
// ������ũ �Ѻκе� �׸��� �ִ� ��(��ǥ�� �������� ����)
class SnakePiece : public Drawable 
{
public:
    SnakePiece() :Drawable(0, 0, SNAKE_BODY)
    {
    }
    SnakePiece(int y, int x, char icon = SNAKE_BODY)
    {
        this->y = y;
        this->x = x;
        this->icon = icon;
    }
    void setIcon(char icon)
    {
        this->icon = icon;
    }
};
// ������ũ�� ť�� ǥ����.
class Snake
{
    std::queue<SnakePiece> pieces;
    Direction cur_direction;
    int maxLength;
public:
    Snake()
    {
        cur_direction = down;
    }

    int getSize()
    {
        return pieces.size();
    }
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
        return SnakePiece(row, col, 'H');
    }
};