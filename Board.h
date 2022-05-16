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
	void addBoarder()
	{
		box(board, 0, 0);
	}
	void add(Drawable drawable)
	{
		addAt(drawable.getY(), drawable.getX(), drawable.getIcon());
	}
	void addAt(int y, int x, chtype ch) 
	{
		mvwaddch(board, y, x, ch);
	}
	chtype getInput()
	{
		return wgetch(board);
	}

	void getEmptyCoordinates(int& y, int& x)
	{
		while (mvwinch(board, y = rand() % height, x = rand() % width) != ' ');
	}
	void clear()
	{
		wclear(board);
		addBoarder();
	}

	void refresh() 
	{
		wrefresh(board);
	}
private:
	WINDOW* board;
	int height, width;
	void construct(int height, int width)
	{
		int xMax, yMax;
		this->height = height;
		this->width = width;
		getmaxyx(stdscr, yMax, xMax);
		board = newwin(height, width, (yMax / 2) - (height / 2), (xMax / 2) - (width / 2));
	}
};