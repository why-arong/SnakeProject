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
		wborder(board_win, '1', '1', '1', '1', '3', '3', '3', '3');
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
		for (int i = 5; i < height - 5; i++)
		{
			mvwaddch(board_win, i, width / 2, '1');
		}
		for (int i = 10; i < width - 10; i++)
		{
			mvwaddch(board_win, height / 2, i, '1');
		}
		mvwaddch(board_win, height / 2, width / 2, '3');
	}

	void makeMap2()
	{
		for (int i = height / 4; i < height; i += 5)
		{
			for (int j = 2; j < 30; j++)
			{
				mvwaddch(board_win, i, j, '1');
			}
		}
		for (int i = height - 3 ; i > 0; i -= 5)
		{
			for (int j = 37; j > 10; j--)
			{

				mvwaddch(board_win, i, j, '1');
			}
		}
	}

	void makeMap3()
	{
		for (int i = 5; i < 18; i++)
		{
			mvwaddch(board_win, 3, i, '1');
			mvwaddch(board_win, 3, i + 18, '1');
		}
		for (int i = 5; i < 16; i++)
		{
			mvwaddch(board_win, 8, i, '1');
			mvwaddch(board_win, 8, i + 18, '1');
		}
		for (int i = 3; i < 9; i++)
		{
			mvwaddch(board_win, i, 5, '1');
			mvwaddch(board_win, i, 23, '1');
		}
		for (int i = 3; i < 16; i++)
		{
			mvwaddch(board_win, i, 17, '1');
			mvwaddch(board_win, i, 35, '1');
		}
		mvwaddch(board_win, 3, 5, '3');
		mvwaddch(board_win, 3, 23, '3');
		mvwaddch(board_win, 8, 5, '3');
		mvwaddch(board_win, 8, 23, '3');
		mvwaddch(board_win, 3, 17, '3');
		mvwaddch(board_win, 3, 35, '3');
	}

	void makeMap4()
	{
		for (int i = 5; i < 18; i++)
		{
			mvwaddch(board_win, 3, i, '1');
			mvwaddch(board_win, 3, i + 18, '1');
		}
		for (int i = 5; i < 16; i++)
		{
			mvwaddch(board_win, 8, i, '1');
			mvwaddch(board_win, 8, i + 18, '1');
		}
		for (int i = 3; i < 9; i++)
		{
			mvwaddch(board_win, i, 5, '1');
			mvwaddch(board_win, i, 23, '1');
		}
		for (int i = 3; i < 9; i++)
		{
			mvwaddch(board_win, i, 17, '1');
			mvwaddch(board_win, i, 35, '1');
		}
		for (int i = 7; i < 12; i++)
		{
			mvwaddch(board_win, i, 19, '1');
		}
		for (int i = 10; i < 30; i++)
		{
			mvwaddch(board_win, 15, i, '1');
		}
		mvwaddch(board_win, 3, 5, '3');
		mvwaddch(board_win, 3, 23, '3');
		mvwaddch(board_win, 8, 5, '3');
		mvwaddch(board_win, 8, 23, '3');
		mvwaddch(board_win, 3, 17, '3');
		mvwaddch(board_win, 3, 35, '3');
	}
	
	void makeMap5()
	{
		for (int i = 1; i < 15; i += 3)
		{
			for (int j = 2; j < 5; j++)
			{
				mvwaddch(board_win, j + i - 1, 6 + 2 * i, '1');
				mvwaddch(board_win, 2 + i, 3 + j + 2 * i, '1');
				mvwaddch(board_win, 2 + i, 6 + 2 * i, '3');
			}
		}
		for (int i = 1; i < 15; i += 3)
		{
			for (int j = 2; j < 5; j++)
			{
				mvwaddch(board_win, 19 - (j + i), 6 + 2 * i, '1');
				mvwaddch(board_win, 19 - (3 + i), 3 + j + 2 * i, '1');
				mvwaddch(board_win, 19 - (3 + i), 6 + 2 * i, '3');
			}
		}
	}

	void makeMap6()
	{
		for (int i = 1; i < 15; i += 3)
		{
			for (int j = 2; j < 5; j++)
			{
				mvwaddch(board_win, j + i - 1, 6 + 2 * i, '1');
				mvwaddch(board_win, 2 + i, 3 + j + 2 * i, '1');
				mvwaddch(board_win, 2 + i, 6 + 2 * i, '3');
			}
		}
		for (int i = 1; i < 15; i += 3)
		{
			for (int j = 2; j < 5; j++)
			{
				mvwaddch(board_win, 19 - (j + i), 6 + 2 * i, '1');
				mvwaddch(board_win, 19 - (3 + i), 3 + j + 2 * i, '1');
				mvwaddch(board_win, 19 - (3 + i), 6 + 2 * i, '3');
			}
		}
		for (int i = 11; i < 30; i++)
		{
			mvwaddch(board_win, 3, i, '1');
			mvwaddch(board_win, 15, i, '1');
		}
		for (int i = 6; i < 13; i++)
		{
			mvwaddch(board_win, i, 8, '1');
			mvwaddch(board_win, i, 32, '1');
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