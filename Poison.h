#pragma once
#include "Drawable.h"
#define POISON_ITEM 'P'
class Poison : public Drawable
{
public:
    Poison(int y, int x)
    {
        this->y = y;
        this->x = x;
        this->icon = POISON_ITEM;
    }
};