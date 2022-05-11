class Boarder {
public:
	getmaxyx(stdscr, yMax, xMax);

	WINDOW* boarder = newwin(BOARDER_ROW, BOARDER_COL, (yMax / 2) - (BOARDER_ROW / 2), (xMax / 2) - (BOARDER_COL / 2));
	box(boarder, 0, 0);
	wrefresh(boarder);
pivate:
	int xMax, yMax;

};