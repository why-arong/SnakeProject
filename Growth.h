#pragma once
#include "Drawable.h"
#define GROWTH_ITEM 'G'
class Growth : public Drawable
{
public:
    Growth(int y, int x)
    {
        this->y = y;
        this->x = x;
        this->icon = GROWTH_ITEM;
    }
private:

};