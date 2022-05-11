#include <curses.h>
#include "Boarder.h"
#define BOARDER_DIM 20
#define BOARDER_ROW BOARDER_DIM
#define BOARDER_COL BOARDER_DIM * 2

int main()
{
	initscr();
	refresh();

	Boarder boarder(BOARDER_ROW, BOARDER_COL);
	boarder.initialize();

	boarder.addAt(5, 5, '*');
	boarder.refresh();
	getch();
	endwin();

	return 0;
}