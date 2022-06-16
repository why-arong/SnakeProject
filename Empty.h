#pragma once
#include "Drawable.h"
#define EMPTY_SPACE ' '
class Empty : public Drawable
{
public:
    Empty(int y, int x)
    {
        this->y = y;
        this->x = x;
        this->icon = EMPTY_SPACE;
    }
};