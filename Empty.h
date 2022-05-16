#pragma once
#include "Drawable.h"
class Empty : public Drawable
{
public:
    Empty(int y, int x)
    {
        this->y = y;
        this->x = x;
        this->icon = ' ';
    }
private:

};