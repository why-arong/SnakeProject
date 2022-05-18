#pragma once
#include <curses.h>
#define TITLE 1
#define START 2
class TitleScreen
{
public:
    TitleScreen()
    {
    }
    void titleOn()
    {
        start_color();
        noecho();
        init_pair(TITLE, COLOR_BLUE, COLOR_GREEN);
        bkgd(COLOR_PAIR(TITLE));
        attroff(COLOR_PAIR(TITLE));
        getch();
    }

    void titleOff()
    {
        init_pair(START, COLOR_WHITE, COLOR_BLACK);
        bkgd(COLOR_PAIR(START));
        refresh();
        attroff(COLOR_PAIR(START));

    }
};