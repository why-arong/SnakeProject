#pragma once
#include "Drawable.h"
class Growth : public Drawable
{
public:
    Growth(int y, int x)
    {
        this->y = y;
        this->x = x;
        this->icon = 'G';
    }
private:

};