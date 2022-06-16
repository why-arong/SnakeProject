#include <curses.h>
#include "Board.h"
#include "SnakeGame.h"
#include "AllclearScreen.h"
#include "GameoverScreen.h"
#define BOARDER_DIM 25
#define BOARDER_ROW BOARDER_DIM
#define BOARDER_COL BOARDER_DIM * 2
int stage_num = 1;
boolean clear_game = true;
AllclearScreen allclear_title;
GameoverScreen gameover_title;

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
		
		if (game.isOver())
		{
			clear_game = false;
			break;
		}
		stage_num++;
	}
	
	if (clear_game)
	{
		allclear_title = AllclearScreen();
		allclear_title.titleOn();
		allclear_title.titleOff();
	}
	else
	{
		gameover_title = GameoverScreen();
		gameover_title.titleOn();
		gameover_title.titleOff();
	}

	// 1. get input from user.
	// 2. update game state.
	// 3. redraw display.
	// 4. go to 1 unless game over.
	getch();
	endwin();

	return 0;
}

	return 0;
}
