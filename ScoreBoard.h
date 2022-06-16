#pragma once

class ScoreBoard
{
public:
    WINDOW* score_win;
    ScoreBoard(int width = 0, int y = 0, int x = 0)
    {
        score_win = newwin(12, width - 30, 1, 70);
    }

    void initialize(int current_size, int max_length, int growth_count, int poison_count, int gate_count)
    {
        clear();
        wborder(score_win, '|', '|', '-', '-', '+', '+', '+', '+');
        mvwprintw(score_win, 1, 7, "Score");
        mvwprintw(score_win, 3, 5, "B : %d / %d", current_size, max_length);  //current_size, max Body_length 
        mvwprintw(score_win, 5, 5, "+ :   %d   ", growth_count); //Growth_item
        mvwprintw(score_win, 7, 5, "- :   %d   ", poison_count); //Poison_item
        mvwprintw(score_win, 9, 5, "G :   %d   ", gate_count); //Gate_cnt
        updateSize(current_size, max_length);
        updateGrowth(growth_count);
        updatePoison(poison_count);
        updateGate(gate_count);
        refresh();
    }


    void updateSize(int current_size, int max_length)
    {
        mvwprintw(score_win, 3, 5, "B : %d / %d", current_size, max_length);
    }
    void updateGrowth(int growth_count)
    {
        mvwprintw(score_win, 5, 5, "+ :   %d   ", growth_count);
    }
    void updatePoison(int poison_count)
    {
        mvwprintw(score_win, 7, 5, "- :   %d   ", poison_count);
    }
    void updateGate(int gate_count)
    {
        mvwprintw(score_win, 9, 5, "G :   %d   ", gate_count);
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