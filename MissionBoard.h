#pragma once

class MissionBoard
{
public:
    WINDOW* mission_win;
    MissionBoard(int width=0, int y=0, int x=0)
    {
        mission_win = newwin(12, width - 30, 15, 70);
    }

    void initialize(int current_size, int max_length, int growth_count, int poison_count, int gate_count)
    {
        clear();
        wborder(mission_win, '|', '|', '-', '-', '+', '+', '+', '+');
        mvwprintw(mission_win, 1, 6, "Mission");
        mvwprintw(mission_win, 3, 5, "B : %d", 5);
        mvwprintw(mission_win, 5, 5, "+ : %d", 2);
        mvwprintw(mission_win, 7, 5, "- : %d", 2);
        mvwprintw(mission_win, 9, 5, "G : %d", 2);
        updateGoal(max_length, growth_count, poison_count, gate_count);
        refresh();
    }
    void updateGoal(int max_length, int growth_count, int poison_count, int gate_count)
    {
        if (max_length < 5)  mvwprintw(mission_win, 3, 12, "(   )");
        else  mvwprintw(mission_win, 3, 12, "( V )");

        if (growth_count < 2)  mvwprintw(mission_win, 5, 12, "(   )");
        else  mvwprintw(mission_win, 5, 12, "( V )");

        if (poison_count < 2)  mvwprintw(mission_win, 7, 12, "(   )");
        else  mvwprintw(mission_win, 7, 12, "( V )");

        if (gate_count < 2) mvwprintw(mission_win, 9, 12, "(   )");
        else  mvwprintw(mission_win, 9, 12, "( V )");
    }

    void clear()
    {
        wclear(mission_win);
    }

    void refresh()
    {
        wrefresh(mission_win);
    }

};
