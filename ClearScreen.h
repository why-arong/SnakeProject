#pragma once
#include <curses.h>
#define BKGD 1
#define START 2
#define EASY 1000
#define NORMAL 500
#define HARD 100
class ClearScreen
{
    int xMax, yMax; // �͹̳� y, x ũ��
    WINDOW* bkgd_win;
    WINDOW* clear_win;
    int mode;

public:
    ClearScreen()
    {
        getmaxyx(stdscr, yMax, xMax);
        int start_row, start_col; // ������ ���� ��ǥ
        this->mode = NORMAL;
        bkgd_win = newwin(yMax, xMax, 0, 0);

        int height = 5;
        int width = xMax / 2;
        start_row = (yMax / 5);
        start_col = (xMax / 2) - (width / 2);
        clear_win = newwin(height, width, start_row, start_col);

    }
    int getMode()
    {
        return mode;
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
        mvwprintw(clear_win, 5 / 2, 17, "<<< Stage Clear >>> ");
        wrefresh(clear_win);

        attroff(COLOR_PAIR(BKGD));
        delwin(bkgd_win);
        delwin(clear_win);
        endwin();

        int input = getch();
        if (input == 'e') mode = EASY;
        else if (input == 'n') mode = NORMAL;
        else if (input == 'h') mode = HARD;
    }

    void titleOff()
    {
        init_pair(START, COLOR_WHITE, COLOR_BLACK);
        bkgd(COLOR_PAIR(START));
        refresh();
        attroff(COLOR_PAIR(START));

    }
};