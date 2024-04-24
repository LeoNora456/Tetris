//
// Created by LeoNora on 17.01.2024.
//

#ifndef TETRIS_TETRIS_H
#define TETRIS_TETRIS_H

#include <iostream>

#include "Piece.h"

//#include <SFML/Graphics.hpp>

#define WIDTH 10
#define HEIGHT 20
#define FIELD_SIZE 40
#define SIDE_SIZE 10

using namespace std;

enum MODE {
    SINGLEPLAYER,
    MULTIPLAYER
};

class Tetris {

public:

    Tetris(int w, int h, MODE mode = SINGLEPLAYER);
    ~Tetris();

    void setBoard(int x, int y, bool value);
    void setScore(int score);
    void setLines(int lines);
    void setLevel(int level);
    void setSpeed(int speed);
    void setLeft(bool left);
    void setRight(bool right);
    void setDown(bool down);
    void setRotate(bool rotate);

    bool getBoard(int x, int y);
    bool **getBoardAll();
    int getBoardWidth();
    int getBoardHeight();
    RectangleShape **getBackground();
    int getScore();
    int getLines();
    int getLevel();
    int getSpeed();
    bool getLeft();
    bool getRight();
    bool getDown();
    bool getRotate();
    Piece getPiece();
    Piece *getNextPiece();


    bool update();
    void draw(RenderWindow *win);
    static void drawEnemy(RenderWindow *win, bool **enemy, RectangleShape **background);

    void movePiece();
    void savePiece();
    void putDown();

private:


    void init();

    void createPiece();
    void deletePiece();
    void checkLines();
    bool checkGameOver();

    int windowWidth, windowHeight;


    int score, lines, level;
    double speed;
    MODE gameMode;

    Piece piece, piece_copy;
    Piece *nextPiece;
    Piece *holdPiece;

    RectangleShape **background;
    bool **board;
    bool left = false, right = false, down = false, rotate = false;
    bool canDown = true, canRotate = true;
    bool settled = false;

    Clock clock{};
    Time currentTime{}, lastTime{};





};


#endif //TETRIS_TETRIS_H
