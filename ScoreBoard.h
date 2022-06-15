#pragma once

class ScoreBoard
{
    WINDOW* score_win;
public:
    
    ScoreBoard(int width=0, int y=0, int x=0)
    {
        score_win = newwin(1, width, y, x);
    }

    void initialize(int initial_score)
    {
        clear();
        mvwprintw(score_win, 0, 1, "Score: ");
        updateScore(initial_score);
        refresh();
    }

    void updateScore(int score)
    {
        mvwprintw(score_win, 0, score_win->_maxx - 10, "%10d", score);
    }
    void clear()
    {
        wclear(score_win);
    }

    void refresh()
    {
        wrefresh(score_win);
    }
};