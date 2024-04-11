//
// Created by LeoNora on 17.01.2024.
//

#ifndef TETRIS_PIECE_H
#define TETRIS_PIECE_H

#include "random"
//#include "Tetris.h"

#include "SFML/Graphics.hpp"


using namespace sf;
using namespace std;

enum Type : int16_t {

    I0 = 0b0000000011110000,
    I90 = 0b0010001000100010,
    I180 = 0b0000000011110000,
    I270 = 0b0010001000100010,

    J0 = 0b0000010001110000,
    J90 = 0b0000011001000100,
    J180 = 0b0000011100010000,
    J270 = 0b0010001001100000,

    L0 = 0b0000000101110000,
    L90 = 0b0000010001000110,
    L180 = 0b0000011101000000,
    L270 = 0b0110001000100000,

    O = 0b0000001100110000,

    S0 = 0b0000001101100000,
    S90 = 0b0000010001100010,
    S180 = 0b0000001101100000,
    S270 = 0b0000010001100010,

    T0 = 0b0000011100100000,
    T90 = 0b0010011000100000,
    T180 = 0b0000001001110000,
    T270 = 0b0000010001100100,

    Z0 = 0b0000011000110000,
    Z90 = 0b0000001001100100,
    Z180 = 0b0000011000110000,
    Z270 = 0b0000001001100100

};

enum Rotation : char {

    R0 = 0,
    R90 = 1,
    R180 = 2,
    R270 = 3

};

class Piece {

public:

    Piece(int x = 4, int y = -1, bool falling = true);



    void setX(int x);
    void setY(int y);
    void setRotation(Rotation rotation);
    void setFalling(bool falling);
    void setSize(int w, int h);
    void setColor(Color color);

    int getX();
    int getY();
    Type getType();
    Rotation getRotation();
    bool isFalling();
    Color getColor();

    static Type getRandomType();
    void rotate();
    [[nodiscard]] int furthestLeft() const;
    [[nodiscard]] int furthestRight() const;
    [[nodiscard]] int furthestDown();
    int furthestUp();
    bool checkBelow(bool **board);

    void draw(RenderWindow *win);

//    Piece &operator=(const Piece &piece);


private:

        int x, y;
        bool falling;

        Type type;
        Rotation rotation;
        RectangleShape **squares;
        Color color;

};


#endif //TETRIS_PIECE_H
