#include <curses.h>
#include "Board.h"
#include "SnakeGame.h"
#define BOARDER_DIM 20
#define BOARDER_ROW BOARDER_DIM
#define BOARDER_COL BOARDER_DIM * 2

int main()
{
	
	initscr();
	refresh();

	noecho(); // 입력해도 윈도우에 보이지 않음.

	SnakeGame game(BOARDER_ROW, BOARDER_COL);

	while (!game.isOver())
	{
		game.processInput();
		game.updateState();
		game.redraw();

	}
	// 1. get input from user.
	// 2. update game state.
	// 3. redraw display.
	// 4. go to 1 unless game over.
	getch();
	endwin();

	return 0;
}