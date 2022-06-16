#pragma once

class MissionBoard
{
public:
    WINDOW* mission_win;
    MissionBoard(int width = 0, int y = 0, int x = 0)
    {
        mission_win = newwin(12, width - 30, 15, 70);
    }

    void initialize(int stage, int current_size, int max_length, int growth_count, int poison_count, int gate_count)
    {
        clear();
        wborder(mission_win, '|', '|', '-', '-', '+', '+', '+', '+');
        mvwprintw(mission_win, 1, 6, "Mission");
        mvwprintw(mission_win, 3, 5, "B : %d", 4 + stage);
        mvwprintw(mission_win, 5, 5, "+ : %d", 1 + stage);
        mvwprintw(mission_win, 7, 5, "- : %d", 1 + stage);
        mvwprintw(mission_win, 9, 5, "G : %d", 1 + stage);
        updateGoal(stage, max_length, growth_count, poison_count, gate_count);
        refresh();
    }
    bool updateGoal(int stage, int max_length, int growth_count, int poison_count, int gate_count)
    {
        if (max_length < 4 + stage)  mvwprintw(mission_win, 3, 12, "(   )");
        else  mvwprintw(mission_win, 3, 12, "( V )");

        if (growth_count < 1 + stage)  mvwprintw(mission_win, 5, 12, "(   )");
        else  mvwprintw(mission_win, 5, 12, "( V )");

        if (poison_count < 1 + stage)  mvwprintw(mission_win, 7, 12, "(   )");
        else  mvwprintw(mission_win, 7, 12, "( V )");

        if (gate_count < 1 + stage) mvwprintw(mission_win, 9, 12, "(   )");
        else  mvwprintw(mission_win, 9, 12, "( V )");

        if (max_length >= 4 + stage && growth_count >= 1 + stage &&
            poison_count >= 1 + stage)
        {
            return true;
        }
        return false;
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