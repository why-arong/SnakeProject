#pragma once
#include <stdlib.h>
#include <curses.h>
#include "Drawable.h"
#include "Time.h"
class Board {
	
public:
	Board()
	{
		construct(0, 0, 300);
	}
	Board(int height, int width, int speed)
	{
		construct(height, width, speed);
	}
	void initialize()
	{
		clear();
		refresh();
	}
	// 박스로 그림.
	void addboard_win()
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
		time_t time_last_input = Time::milliseconds();
		
		chtype input = wgetch(board_win);
		chtype new_input = ERR; // curses에서 -1로 정의됨.
		
		setWTimeout(0);
		while (time_last_input + timeout >= Time::milliseconds())
		{
			new_input = wgetch(board_win);
		}
		setWTimeout(timeout);

		if (new_input != ERR)
		{
			input = new_input;
		}
		return input;
	}

	void getEmptyCoordinates(int& y, int& x)
	{
		while (mvwinch(board_win, y = rand() % height, x = rand() % width) != ' ');
	}
	chtype getCharAt(int y, int x)
	{
		return mvwinch(board_win, y, x);
	}
	void setWTimeout(int timeout)
	{
		wtimeout(board_win, timeout);
	}
	int getTimeout()
	{
		return timeout;
	}
	void clear()
	{
		wclear(board_win);
		addboard_win();
	}

	void refresh() 
	{
		wrefresh(board_win);
	}
	int getStartRow()
	{
		return start_row;
	}
	int getStartCol()
	{
		return start_col;
	}
private:
	WINDOW* board_win;
	int height, width, start_row, start_col;
	int timeout;
	void construct(int height, int width, int speed)
	{
		int xMax, yMax;
		this->height = height;
		this->width = width;
		getmaxyx(stdscr, yMax, xMax);

		start_row = (yMax / 2) - (height / 2);
		start_col = (xMax / 2) - (width / 2);
		board_win = newwin(height, width, start_row, start_col);
		timeout = speed;

		setWTimeout(speed);
		keypad(board_win, true);
	}
};