#pragma once
#include "Drawable.h"
#define GATE '?'
class Gate : public Drawable
{
public:
    Gate(int y, int x)
    {
        this->y = y;
        this->x = x;
        this->icon = GATE;
    }
};