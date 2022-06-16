#pragma once
#include <curses.h>
#define BKGD 1
#define START 2

class AllclearScreen
{
    int xMax, yMax; // 터미널 y, x 크기
    WINDOW* bkgd_win;
    WINDOW* clear_win;

public:
    AllclearScreen()
    {
        getmaxyx(stdscr, yMax, xMax);
        int start_row, start_col; // 윈도우 시작 좌표

        bkgd_win = newwin(yMax, xMax, 0, 0);

        int height = 5;
        int width = xMax / 2;
        start_row = (yMax / 5);
        start_col = (xMax / 2) - (width / 2);
        clear_win = newwin(height, width, start_row, start_col);

    }

    void titleOn()
    {
        start_color();
        noecho();
        init_pair(BKGD, COLOR_BLACK, COLOR_YELLOW);
        init_pair(START, COLOR_WHITE, COLOR_GREEN);

        wbkgd(bkgd_win, COLOR_PAIR(BKGD));
        wclear(bkgd_win);
        wattron(bkgd_win, COLOR_PAIR(BKGD));
        wborder(bkgd_win, '*', '*', '*', '*', '*', '*', '*', '*');
        wrefresh(bkgd_win);

        wbkgd(clear_win, COLOR_PAIR(START));
        wclear(clear_win);
        wattron(clear_win, COLOR_PAIR(START));
        mvwprintw(clear_win, 5 / 2, 17, "<<< All Clear!! >>> ");
        wrefresh(clear_win);

        attroff(COLOR_PAIR(BKGD));
        delwin(bkgd_win);
        delwin(clear_win);
        endwin();

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