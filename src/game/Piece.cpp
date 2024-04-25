//
// Created by LeoNora on 17.01.2024.
//

#include "../../include/Piece.h"
#include "../../include/Tetris.h"

Piece::Piece(int x, int y, bool falling) {


    this->x = x;
    this->y = y;
    this->type = getRandomType();
//    this->type = Z0;
    this->rotation = R0;
    this->falling = falling;
//    cout << "PIECE CREATED: \t\tTYPE: " << (int) type << endl;
//    cout << "PIECE_DRAWN: " << piece_drawn << endl;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 7);

    color = colors[dis(gen)];

    squares = new RectangleShape *[4];
    for (int i = 0; i < 4; ++i) {
        squares[i] = new RectangleShape[4];
        for (int j = 0; j < 4; ++j) {
            squares[i][j] = RectangleShape(Vector2f(FIELD_SIZE, FIELD_SIZE));
            squares[i][j].setOutlineColor(Color(255, 255, 255, 255));
            squares[i][j].setOutlineThickness(1);
            squares[i][j].setFillColor(color);
        }
    }

}

void Piece::setX(int x) {
    this->x = x;
}
void Piece::setY(int y) {
    this->y = y;
}
void Piece::setRotation(Rotation rotation) {
    this->rotation = rotation;
}
void Piece::setFalling(bool falling) {
    this->falling = falling;
}
void Piece::setSize(int w, int h) {

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                squares[i][j].setSize(Vector2f(w, h));
            }
        }
}
void Piece::setColor(Color color) {
    this->color = color;
}

int Piece::getX() {
    return x;
}
int Piece::getY() {
    return y;
}
Type Piece::getType() {
    return type;
}
Rotation Piece::getRotation() {
    return rotation;
}
bool Piece::isFalling() {
    return falling;
}
Color Piece::getColor() {
    return color;
}

Type Piece::getRandomType() {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 6);

    int random = dis(gen);

    if (random == 0) {
        return I0;
    } else if (random == 1) {
        return J0;
    } else if (random == 2) {
        return L0;
    } else if (random == 3) {
        return O;
    } else if (random == 4) {
        return S0;
    } else if (random == 5) {
        return T0;
    } else if (random == 6) {
        return Z0;
    }
    return I90;
}

void Piece::rotate() {

    if (rotation == R0) {
        rotation = R90;
        switch (type) {
            case I0:
                type = I90;
                break;
            case J0:
                type = J90;
                break;
            case L0:
                type = L90;
                break;
            case O:
                type = O;
                break;
            case S0:
                type = S90;
                break;
            case T0:
                type = T90;
                break;
            case Z0:
                type = Z90;
                break;
        }
    } else if (rotation == R90) {
        rotation = R180;
        switch (type) {
            case I90:
                type = I180;
                break;
            case J90:
                type = J180;
                break;
            case L90:
                type = L180;
                break;
            case O:
                type = O;
                break;
            case S90:
                type = S180;
                break;
            case T90:
                type = T180;
                break;
            case Z90:
                type = Z180;
                break;
        }
    } else if (rotation == R180) {
        rotation = R270;
        switch (type) {
            case I180:
                type = I270;
                break;
            case J180:
                type = J270;
                break;
            case L180:
                type = L270;
                break;
            case O:
                type = O;
                break;
            case S180:
                type = S270;
                break;
            case T180:
                type = T270;
                break;
            case Z180:
                type = Z270;
                break;
        }
    } else if (rotation == R270) {
        rotation = R0;
        switch (type) {
            case I270:
                type = I0;
                break;
            case J270:
                type = J0;
                break;
            case L270:
                type = L0;
                break;
            case O:
                type = O;
                break;
            case S270:
                type = S0;
                break;
            case T270:
                type = T0;
                break;
            case Z270:
                type = Z0;
                break;
        }
    }

}
int Piece::furthestLeft() const {

    for (int j = 0, k = 1; j < 4; ++j, k >>= 17) {
        for (int i = 0; i < 4; ++i, k <<= 4) {
            if ((type & k) == k) {
                return x + j;
            }
        }
    }
    return -1;
}
int Piece::furthestRight() const {

    for (int j = 3, k = 8; j >= 0; --j, k >>= 17) {
        for (int i = 0; i < 4; ++i, k <<= 4) {
            if ((type & k) == k) {
                return x + j;
            }
        }
    }
    return -1;
}
int Piece::furthestDown() {

    for (int i = 3, k = 1 << 15; i >= 0; --i) {
        for (int j = 0; j < 4; ++j, k >>= 1) {
            if ((type & k) == k) {
                return y + i;
            }
        }
    }
    return -1;
}
int Piece::furthestUp() {

    for (int i = 0, k = 1; i < 4; ++i) {
        for (int j = 0; j < 4; ++j, k <<= 1) {
            if ((type & k) == k) {
                return y + i;
            }
        }
    }
    return -1;
}
bool Piece::checkBelow(bool **board) {
    for (int i = 0, k = 1; i < 4; ++i) {
        for (int j = 0; j < 4 ; ++j, k <<= 1) {
            if ((type & k) == k) {
                if (y + i == HEIGHT - 1 || board[y + i + 1][x + j]) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Piece::draw(RenderWindow *win) {


    for (int i = 0, k = 1; i < 4; ++i) {
        for (int j = 0; j < 4; ++j, k <<= 1) {
            if ((type & k) == k) {

                squares[i][j].setPosition(Vector2f(WIDTH * FIELD_SIZE + (x + j) * SIDE_SIZE + j, (y + i) * SIDE_SIZE + i));

                win->draw(squares[i][j]);
            }
        }
    }

}
