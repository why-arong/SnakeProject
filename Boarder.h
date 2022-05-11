#pragma once

class Boarder {
	WINDOW* boarder;
public:
	Boarder(int height, int width){
		int xMax, yMax;
		getmaxyx(stdscr, yMax, xMax);
		boarder = newwin(height, width, (yMax / 2) - (height / 2), (xMax / 2) - (width / 2));
	}
	void initialize()
	{
		clear();
		refresh();
	}
	void addBoarder()
	{
		box(boarder, 0, 0);
	}

	void addAt(int y, int x, chtype ch) 
	{
		mvwaddch(boarder, y, x, ch);
	}
	chtype getInput()
	{
		return wgetch(boarder);
	}
	void clear()
	{
		wclear(boarder);
		addBoarder();
	}

	void refresh() {
		wrefresh(boarder);
	}

};