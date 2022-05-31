#pragma once
#include <curses.h>
#define BKGD 1
#define START 2
// Mode Setting
#define EASY 1000
#define NORMAL 500
#define HARD 100

class TitleScreen
{
    int mode;
    int xMax, yMax; // 터미널 y, x 크기
    WINDOW* bkgd_win;
    WINDOW* title_win;

public:
    TitleScreen()
    {
        getmaxyx(stdscr, yMax, xMax);
        int start_row, start_col; // 윈도우 시작 좌표
       
        bkgd_win = newwin(yMax, xMax, 0, 0);

        int height = 5;
        int width = xMax / 2;
        start_row = (yMax / 5);
        start_col = (xMax / 2) - (width / 2);
        title_win = newwin(height, width, start_row, start_col);

        mode = NORMAL;
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
        mvwprintw(bkgd_win, (yMax / 1.8) , (xMax / 2) - 8, "Press the button!");
        mvwprintw(bkgd_win, (yMax / 1.8) + 5, (xMax / 2) - 8, "EASY: press E!!");
        mvwprintw(bkgd_win, (yMax / 1.8) + 8, (xMax / 2) - 8, "NORMAL: press N!!");
        mvwprintw(bkgd_win, (yMax / 1.8) + 11, (xMax / 2) - 8, "HARD: press H!!");
        wborder(bkgd_win, '*', '*', '*', '*', '*', '*', '*', '*');
        wrefresh(bkgd_win);

        wbkgd(title_win, COLOR_PAIR(START));
        wclear(title_win);
        wattron(title_win, COLOR_PAIR(START));
        mvwprintw(title_win, 5/2, 17, "<<< 99's SNAKE GAME >>> ");
        wrefresh(title_win);

        attroff(COLOR_PAIR(BKGD));
        delwin(bkgd_win);
        delwin(title_win);
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