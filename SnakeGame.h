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
// 스네이크 게임의 전체적인 컨트롤을 맡는 클래스 
// 스네이크의 움직임, 부딪칠 때의 상황 등을 제어
class SnakeGame 
{
    Board board;
    Growth* growth;
    bool game_over;
    TitleScreen title;
    Snake snake;
    ScoreBoard scoreboard;
    int score;
    // 기본적으로 스네이크라는 큐가 머리 방향으로 증가하는 형태인데
    // 증가되는 곳이 빈칸이라면 즉, 열매 없이 그냥 막 움직일 때는 머리부분 증가했으면 꼬리는 pop 되어야함(removepiece)
    // 증가되는 곳이 열매가 있는 곳이라면 열매를 먹은거니까 점수 올리고 다음 열매를 만들기 위해서 열매 delete
    // 열매를 먹었으니 따로 pop을 안시켜줌으로써 스네이크가 길어지는 것임
    
    // 우선 열매, 빈칸이 아니면 (벽같은) 게임오버 되게 설정함. 나중에는 게임오버 스크린이 띄워지도록 바꿔야함.
    void handleNextGrowth(SnakePiece next)
    {
        if (growth) {

            switch (board.getCharAt(next.getY(), next.getX()))
            {
            case 'G':
                eatGrowth();
                break;
            case ' ':
            {
                int emptyRow = snake.tail().getY();
                int emptyCol = snake.tail().getX();
                board.add(Empty(emptyRow, emptyCol));
                snake.removePiece();
                break;
            }
            default:
                game_over = true;
                break;
            }
        }
        board.add(next);
        snake.addPiece(next);
    }
    // 비어있는 랜덤 좌표를 하나 받아서 y, x에 저장하고 board에 성장열매 그림.
    void createGrowth()
    {
        int y, x;
        board.getEmptyCoordinates(y, x);
        growth = new Growth(y, x);
        board.add(*growth);
    }
    // 성장열매 먹으면 다음 성장열매 만들기 위해서 삭제하고 점수 올림.
    void eatGrowth()
    {
        delete growth;
        growth = NULL;
        score += 100;
        scoreboard.updateScore(score);
    }
    
public:
    SnakeGame(int height, int width) :growth(NULL)
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
        initialize();
    }
    ~SnakeGame()
    {
        delete growth;
    }
    void initialize()
    {
        score = 0;
        scoreboard.initialize(score);
        growth = NULL;
        board.initialize();


        // 임시로 초기화 부분에 맵을 그림.
        board.makeMap6();


        game_over = false;
        srand(time(NULL));

        // snake 초기화 (4개짜리)
        snake.setDirection(down);
        handleNextGrowth(SnakePiece(11, 11));
        handleNextGrowth(snake.nextHead());
        handleNextGrowth(snake.nextHead());
        snake.setDirection(right);
        handleNextGrowth(snake.nextHead());
        if (growth == NULL) createGrowth();
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
        handleNextGrowth(snake.nextHead());
        if (growth == NULL) createGrowth();
    }

    void redraw()
    {
        board.refresh();
        scoreboard.refresh();
    }

    bool isOver()
    {
        return game_over;
    }
    int getScore()
    {
        return score;
    }
    
};