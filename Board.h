#pragma once
#include <stdlib.h>
#include <curses.h>
#include "Drawable.h"
class Board {
	
public:
	Board()
	{
		construct(0, 0);
	}
	Board(int height, int width)
	{
		construct(height, width);
	}
	void initialize()
	{
		clear();
		refresh();
	}
	void addboard_winer()
	{
		box(board_win, 0, 0);
	}
	void add(Drawable drawable)
	{
		addAt(drawable.getY(), drawable.getX(), drawable.getIcon());
	}
	void addAt(int y, int x, chtype ch) 
	{
		mvwaddch(board_win, y, x, ch);
	}
	chtype getInput()
	{
		return wgetch(board_win);
	}

	void getEmptyCoordinates(int& y, int& x)
	{
		while (mvwinch(board_win, y = rand() % height, x = rand() % width) != ' ');
	}
	void clear()
	{
		wclear(board_win);
		addboard_winer();
	}

	void refresh() 
	{
		wrefresh(board_win);
	}
private:
	WINDOW* board_win;
	int height, width;
	void construct(int height, int width)
	{
		int xMax, yMax;
		this->height = height;
		this->width = width;
		getmaxyx(stdscr, yMax, xMax);
		board_win = newwin(height, width, (yMax / 2) - (height / 2), (xMax / 2) - (width / 2));
		wtimeout(board_win, 500);

		keypad(board_win, true);
	}
};