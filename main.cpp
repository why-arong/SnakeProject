#include <curses.h>
#include "Board.h"
#include "SnakeGame.h"
#define BOARDER_DIM 25
#define BOARDER_ROW BOARDER_DIM
#define BOARDER_COL BOARDER_DIM * 2
int stage_num = 1;

int main()
{
	initscr();
	resize_term(30, 110);
	refresh();
	curs_set(0);

	while (stage_num <= 4)
	{
		SnakeGame game(BOARDER_ROW, BOARDER_COL, stage_num);

		while (!(game.isOver() || game.isClear()))
		{
			game.processInput();
			game.updateState();
			game.redraw();
		}
		
		if (game.isOver()) break;
		stage_num++;
	}
	// 1. get input from user.
	// 2. update game state.
	// 3. redraw display.
	// 4. go to 1 unless game over.
	getch();
	endwin();

	return 0;
}
