#pragma once
// Controller class

#include <curses.h>
#include <time.h>
#include <stdlib.h>
#include "Board.h"
#include "Drawable.h"
#include "Growth.h"
#include "Empty.h"
#include "TitleScreen.h"
#include "Snake.h"
#include "ScoreBoard.h"
#include "MissionBoard.h"
#include "Poison.h"
#include "Gate.h"
#include <vector>
using namespace std;
// 스네이크 게임의 전체적인 컨트롤을 맡는 클래스 
// 스네이크의 움직임, 부딪칠 때의 상황 등을 제어
class SnakeGame
{
    Board board;
    Growth growth;
    Poison poison;
    Gate* gate1, * gate2;
    bool game_over;
    bool game_clear;
    TitleScreen title;
    Snake snake;
    ScoreBoard scoreboard;
    MissionBoard missionboard;
    int score;
    time_t start;
    int growth_vec[3][2], poison_vec[3][2];
    Gate* gate_vec[2];
    int r1, r2;
    int growth_count, poison_count, gate_count;
    int max_length = 3, current_size = 3;
    int stage_num = 1;

    void handleSnake(SnakePiece next)
    {
        int y = next.getY(); int x = next.getX();
        // 
        if (y == gate_vec[0]->getY() && x == gate_vec[0]->getX())
        {
            int emptyRow = snake.tail().getY();
            int emptyCol = snake.tail().getX();
            board.add(Empty(emptyRow, emptyCol));
            snake.removePiece();
            board.add(SnakePiece(snake.head().getY(), snake.head().getX(), '+'));

            int exit_y = findExit(gate_vec[1]->getY(), gate_vec[1]->getX())[0];
            int exit_x = findExit(gate_vec[1]->getY(), gate_vec[1]->getX())[1];
            SnakePiece exit(exit_y, exit_x);
            board.add(exit);
            snake.addPiece(exit);
            deleteGate();
            return;
        }
        else if (y == gate_vec[1]->getY() && x == gate_vec[1]->getX())
        {
            int emptyRow = snake.tail().getY();
            int emptyCol = snake.tail().getX();
            board.add(Empty(emptyRow, emptyCol));
            snake.removePiece();
            board.add(SnakePiece(snake.head().getY(), snake.head().getX(), '+'));

            int exit_y = findExit(gate_vec[0]->getY(), gate_vec[0]->getX())[0];
            int exit_x = findExit(gate_vec[0]->getY(), gate_vec[0]->getX())[1];
            SnakePiece exit(exit_y, exit_x);
            board.add(exit);
            snake.addPiece(exit);
            deleteGate();

            return;
        }
        switch (board.getCharAt(y, x))
        {
        case 'G':
            deleteGrowth();
            break;
        case ' ':
        {
            int emptyRow = snake.tail().getY();
            int emptyCol = snake.tail().getX();
            board.add(Empty(emptyRow, emptyCol));
            snake.removePiece();
            break;
        }

        case 'P':
        {
            deletePoison();
            int emptyRow1 = snake.tail().getY();
            int emptyCol1 = snake.tail().getX();
            board.add(Empty(emptyRow1, emptyCol1));
            snake.removePiece();
            int emptyRow2 = snake.tail().getY();
            int emptyCol2 = snake.tail().getX();
            board.add(Empty(emptyRow2, emptyCol2));
            snake.removePiece();
            if (snake.getSize() < 2) game_over = true;
            break;
        }
        default:
            game_over = true;
            break;
        }
        board.add(SnakePiece(snake.head().getY(), snake.head().getX(), '+'));
        board.add(next);
        snake.addPiece(next);
    }

    void createGrowth()
    {
        int y, x;
        r1 = rand() % 3 + 1;
        for (int i = 0; i < r1; i++)
        {

            board.getEmptyCoordinates(y, x);
            growth = Growth(y, x);
            board.add(growth);
            growth_vec[i][0] = y;
            growth_vec[i][1] = x;
        }

    }
    void clearGrowth()
    {
        for (int i = 0; i < r1; i++)
        {
            int y = growth_vec[i][0];
            int x = growth_vec[i][1];
            board.add(Empty(y, x));
        }
    }
    void createPoison()
    {
        int y, x;
        r2 = rand() % 3 + 1;
        for (int i = 0; i < r2; i++)
        {
            board.getEmptyCoordinates(y, x);
            poison = Poison(y, x);
            board.add(poison);
            poison_vec[i][0] = y;
            poison_vec[i][1] = x;
        }
    }
    void clearPoison()
    {
        for (int i = 0; i < r2; i++)
        {
            int y = poison_vec[i][0];
            int x = poison_vec[i][1];
            board.add(Empty(y, x));
        }
    }

    void deleteGrowth()
    {
        growth_count++;
        scoreboard.updateGrowth(growth_count);
        current_size++;
        max_length = max(max_length, current_size);
        scoreboard.updateSize(current_size, max_length);
        game_clear = missionboard.updateGoal(stage_num, max_length, growth_count, poison_count, gate_count);
    }
    void deletePoison()
    {
        poison_count++;
        scoreboard.updatePoison(poison_count);
        current_size--;
        scoreboard.updateSize(current_size, max_length);
        game_clear = missionboard.updateGoal(stage_num, max_length, growth_count, poison_count, gate_count);
    }

    void createGate()
    {
        int y, x;
        board.getGateCoordinates(y, x);
        gate1 = new Gate(y, x);
        board.add(*gate1);
        gate_vec[0] = gate1;

        board.getGateCoordinates(y, x);
        gate2 = new Gate(y, x);
        gate_vec[1] = gate2;
        board.add(*gate2);
    }
    void deleteGate()
    {
        gate_count++; // 진입
        board.addAt(gate_vec[0]->getY(), gate_vec[0]->getX(), ':');
        board.addAt(gate_vec[1]->getY(), gate_vec[1]->getX(), ':');
        gate1 = NULL;
        gate2 = NULL;

        scoreboard.updateGate(gate_count);
        game_clear = missionboard.updateGoal(stage_num, max_length, growth_count, poison_count, gate_count);
    }
    int* findExit(int y, int x)
    {
        int arr[] = { -1, -1 };
        Direction cur_direction = snake.getDirection();
        switch (cur_direction)
        {
        case up:
            if (board.getCharAt(y - 1, x) != ' ')
            {
                if (board.getCharAt(y, x + 1) == ' ')
                {
                    x++;
                    snake.setDirection(right);
                    break;
                }
                else if (board.getCharAt(y, x - 1) == ' ')
                {
                    x--;
                    snake.setDirection(left);
                    break;
                }
                else if (board.getCharAt(y + 1, x) == ' ')
                {
                    y++;
                    snake.setDirection(down);
                    break;
                }
            }
            y--;
            break;
        case down:
            if (board.getCharAt(y + 1, x) != ' ')
            {
                if (board.getCharAt(y, x - 1) == ' ')
                {
                    x--;
                    snake.setDirection(left);
                    break;
                }
                else if (board.getCharAt(y, x + 1) == ' ')
                {
                    x++;
                    snake.setDirection(right);
                    break;
                }
                else if (board.getCharAt(y - 1, x) == ' ')
                {
                    y--;
                    snake.setDirection(up);
                    break;
                }
            }
            y++;
            break;
        case left:
            if (board.getCharAt(y, x - 1) != ' ')
            {
                if (board.getCharAt(y - 1, x) == ' ')
                {
                    y--;
                    snake.setDirection(up);
                    break;
                }
                else if (board.getCharAt(y + 1, x) == ' ')
                {
                    y++;
                    snake.setDirection(down);
                    break;
                }
                else if (board.getCharAt(y, x + 1) == ' ')
                {
                    x++;
                    snake.setDirection(right);
                    break;
                }
            }
            x--;
            break;
        case right:
            if (board.getCharAt(y, x + 1) != ' ')
            {
                if (board.getCharAt(y + 1, x) == ' ')
                {
                    y++;
                    snake.setDirection(down);
                    break;
                }
                else if (board.getCharAt(y - 1, x) == ' ')
                {
                    y--;
                    snake.setDirection(up);
                    break;
                }
                else if (board.getCharAt(y, x - 1) == ' ')
                {
                    x--;
                    snake.setDirection(left);
                    break;
                }
            }
            x++;
            break;
        default:
            break;
        }
        arr[0] = y; arr[1] = x;
        return arr;
    }
public:
    SnakeGame(int height, int width, int stage) :r1(0), r2(0),
        growth(0, 0), poison(0, 0), gate1(NULL), gate2(NULL),
        growth_count(0), poison_count(0), gate_count(0)
    {
        // 타이틀 초기화, 유저가 정한 스피드(1틱을 몇초로 하느냐)설정

        title = TitleScreen();
        title.titleOn();
        title.titleOff();
        int speed = title.getMode();

        // main.cpp에서 정해진 높이 너비로 박스 하나 그림
        board = Board(height, width, speed);
        int sb_row = board.getStartRow() + height;
        int sb_col = board.getStartCol();
        scoreboard = ScoreBoard(width, sb_row, sb_col);
        missionboard = MissionBoard(width, sb_row, sb_col);
        initialize(stage);
    }

    void initialize(int stage)
    {
        game_over = false;
        game_clear = false;
        stage_num = stage;
        start = time(NULL);
        score = 0;
        scoreboard.initialize(current_size, max_length, growth_count, poison_count, gate_count);
        missionboard.initialize(stage, current_size, max_length, growth_count, poison_count, gate_count);
        board.initialize();


        if (stage == 1) board.makeMap1();
        else if (stage == 2) board.makeMap2();
        else if (stage == 3) board.makeMap3();
        else if (stage == 4) board.makeMap4();

        srand(time(NULL));

        initSnake();
        createGrowth();
        createPoison();
        createGate();
    }
    void initSnake()
    {
        snake.setDirection(down);
        board.add(SnakePiece(11, 11));
        snake.addPiece(SnakePiece(11, 11));

        board.add(SnakePiece(12, 11));
        snake.addPiece(SnakePiece(12, 11));

        board.add(SnakePiece(13, 11, '@'));
        snake.addPiece(SnakePiece(13, 11, '@'));

    }
    void processInput()
    {
        chtype input = board.getInput();// 입력 없으면 ERR(-1) 리턴.
        int pre_timeout = board.getTimeout();
        // 입력과 반대방향 일 때는 방향 바꿔주지 않음
        switch (input)
        {
        case KEY_UP:
        case 'w':
            if (snake.getDirection() == down) break;
            snake.setDirection(up);
            break;
        case KEY_DOWN:
        case 's':
            if (snake.getDirection() == up) break;
            snake.setDirection(down);
            break;
        case KEY_LEFT:
        case 'a':
            if (snake.getDirection() == right) break;
            snake.setDirection(left);
            break;
        case KEY_RIGHT:
        case 'd':
            if (snake.getDirection() == left) break;
            snake.setDirection(right);
            break;
        case 'p':
            while (board.getInput() != 'p');
            board.setWTimeout(pre_timeout);
            break;

        default:
            break;
        }
    }

    void updateState()
    {
        handleSnake(snake.nextHead());
        time_t cur_time = time(NULL);
        double  diff_time = difftime(cur_time, start);
        if (diff_time > 10)
        {
            start = time(NULL);
            clearGrowth();
            createGrowth();
            clearPoison();
            createPoison();
        }
        if (gate1 == NULL && current_size >= 4) createGate();
    }

    void redraw()
    {
        board.refresh();
        scoreboard.refresh();
        missionboard.refresh();
    }

    bool isOver()
    {
        return game_over;
    }

    bool isClear()
    {
        return game_clear;
    }

    int getScore()
    {
        return score;
    }

};
