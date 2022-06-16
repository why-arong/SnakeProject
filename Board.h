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
		wborder(board_win, ':', ':', ':', ':', '*', '*', '*', '*');
		//box(board_win, 0, 0);
	}
	// 보드판에 그릴수 있는 객체를 그리기(객체는 그냥 x,y,icon 뽑아서 addAt에 넘기기 위함일 뿐)
	void add(Drawable drawable)
	{
		addAt(drawable.getY(), drawable.getX(), drawable.getIcon());
	}
	void addAt(int y, int x, chtype ch)
	{
		mvwaddch(board_win, y, x, ch);
	}

	

	void makeMap1()
	{
		for (int i = 7; i < 22; i++)
		{
			mvwaddch(board_win, 3, i, ':');
			mvwaddch(board_win, 3, i + 18, ':');
		}
		for (int i = 7; i < 20; i++)
		{
			mvwaddch(board_win, 10, i, ':');
			mvwaddch(board_win, 10, i + 18, ':');
		}
		for (int i = 3; i < 10; i++)
		{
			mvwaddch(board_win, i, 7, ':');
			mvwaddch(board_win, i, 25, ':');
		}
		for (int i = 3; i < 20; i++)
		{
			mvwaddch(board_win, i, 21, ':');
			mvwaddch(board_win, i, 39, ':');
		}
		mvwaddch(board_win, 3, 7, '*');
		mvwaddch(board_win, 3, 25, '*');
		mvwaddch(board_win, 10, 7, '*');
		mvwaddch(board_win, 10, 25, '*');
		mvwaddch(board_win, 3, 21, '*');
		mvwaddch(board_win, 3, 39, '*');
	}

	void makeMap2()
	{
		for (int i = 7; i < 22; i++)
		{
			mvwaddch(board_win, 3, i, ':');
			mvwaddch(board_win, 3, i + 18, ':');
		}
		for (int i = 7; i < 20; i++)
		{
			mvwaddch(board_win, 10, i, ':');
			mvwaddch(board_win, 10, i + 18, ':');
		}
		for (int i = 3; i < 10; i++)
		{
			mvwaddch(board_win, i, 7, ':');
			mvwaddch(board_win, i, 25, ':');
		}
		for (int i = 3; i < 11; i++)
		{
			mvwaddch(board_win, i, 21, ':');
			mvwaddch(board_win, i, 39, ':');
		}
		for (int i = 9; i < 15; i++)
		{
			mvwaddch(board_win, i, 23, ':');
		}
		for (int i = 10; i < 35; i++)
		{
			mvwaddch(board_win, 18, i, ':');
		}
		mvwaddch(board_win, 3, 7, '*');
		mvwaddch(board_win, 3, 25, '*');
		mvwaddch(board_win, 10, 7, '*');
		mvwaddch(board_win, 10, 25, '*');
		mvwaddch(board_win, 3, 21, '*');
		mvwaddch(board_win, 3, 39, '*');
	}

	void makeMap3()
	{
		for (int i = 1; i < 20; i += 3)
		{
			for (int j = 2; j < 5; j++)
			{
				mvwaddch(board_win, j + i - 1, 4 + 2 * i, ':');
				mvwaddch(board_win, 2 + i, 1 + j + 2 * i, ':');
				mvwaddch(board_win, 2 + i, 4 + 2 * i, '*');
			}
		}
		for (int i = 1; i < 20; i += 3)
		{
			for (int j = 2; j < 5; j++)
			{
				mvwaddch(board_win, 25 - (j + i), 6 + 2 * i, ':');
				mvwaddch(board_win, 25 - (3 + i), 3 + j + 2 * i, ':');
				mvwaddch(board_win, 25 - (3 + i), 6 + 2 * i, '*');
			}
		}
	}

	void makeMap4()
	{
		for (int i = 1; i < 20; i += 3)
		{
			for (int j = 2; j < 5; j++)
			{
				mvwaddch(board_win, j + i - 1, 4 + 2 * i, ':');
				mvwaddch(board_win, 2 + i, 1 + j + 2 * i, ':');
				mvwaddch(board_win, 2 + i, 4 + 2 * i, '*');
			}
		}
		for (int i = 1; i < 20; i += 3)
		{
			for (int j = 2; j < 5; j++)
			{
				mvwaddch(board_win, 25 - (j + i), 6 + 2 * i, ':');
				mvwaddch(board_win, 25 - (3 + i), 3 + j + 2 * i, ':');
				mvwaddch(board_win, 25 - (3 + i), 6 + 2 * i, '*');
			}
		}
		for (int i = 11; i < 40; i++)
		{
			mvwaddch(board_win, 21, i, ':');
		}
		for (int i = 9; i < 42; i++)
		{
			mvwaddch(board_win, 3, i, ':');
		}
		for (int i = 6; i < 19; i++)
		{
			mvwaddch(board_win, i, 7, ':');
			mvwaddch(board_win, i, 43, ':');
		}

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
	void getGateCoordinates(int& y, int& x)
	{
		while (mvwinch(board_win, y = rand() % height, x = rand() % width) != ':');
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
		start_col = (xMax / 2) - (width / 1);
		board_win = newwin(height, width, start_row, start_col);
		timeout = speed;

		setWTimeout(speed);
		keypad(board_win, true);
	}
};
