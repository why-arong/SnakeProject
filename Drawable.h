#pragma once

class Drawable {

public:
    Drawable() :y(0), x(0), icon(' ') {}
    Drawable(int y, int x, chtype ch) :y(y), x(x), icon(ch) {}

    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    chtype getIcon()
    {
        return icon;
    }
protected:
    int y, x;
    chtype icon;
};