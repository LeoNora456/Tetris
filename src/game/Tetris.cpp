//
// Created by LeoNora on 17.01.2024.
//

#include "../../include/Tetris.h"

Tetris::Tetris(int w, int h, MODE mode) {

    gameMode = mode;
    windowWidth = w;
    windowHeight = h;

    init();

}
Tetris::~Tetris() {

    for (int i = 0; i < HEIGHT; ++i) {
        delete[] background[i];
    }
    delete[] background;

    delete[] nextPiece;

}

void Tetris::setBoard(int x, int y, bool value) {
    board[x][y] = value;
}
void Tetris::setScore(int score) {
    this->score = score;
}
void Tetris::setLines(int lines) {
    this->lines = lines;
}
void Tetris::setLevel(int level) {
    this->level = level;
}
void Tetris::setSpeed(int speed) {
    this->speed = speed;
}
void Tetris::setLeft(bool left) {
    this->left = left;
}
void Tetris::setRight(bool right) {
    this->right = right;
}
void Tetris::setDown(bool down) {
    this->down = down;
}
void Tetris::setRotate(bool rotate) {
    this->rotate = rotate;
}

bool Tetris::getBoard(int x, int y) {
    return board[y][x];
}
bool **Tetris::getBoardAll() {
    return board;
}
int Tetris::getBoardWidth() {
    return WIDTH;
}
int Tetris::getBoardHeight() {
    return HEIGHT;
}
RectangleShape **Tetris::getBackground() {
    return background;
}
int Tetris::getScore() {
    return score;
}
int Tetris::getLines() {
    return lines;
}
int Tetris::getLevel() {
    return level;
}
int Tetris::getSpeed() {
    return speed;
}
bool Tetris::getLeft() {
    return left;
}
bool Tetris::getRight() {
    return right;
}
bool Tetris::getDown() {
    return down;
}
bool Tetris::getRotate() {
    return rotate;
}
Piece Tetris::getPiece() {
    return piece;
}
Piece *Tetris::getNextPiece() {
    return nextPiece;
}


bool Tetris::update() {

    bool gameOver = false;

    movePiece();

    currentTime = clock.getElapsedTime();
    Time diff = currentTime - lastTime;
    double timePassed = diff.asMilliseconds();

    if (timePassed >= 1000 * speed) {
        lastTime = currentTime;
        if (!piece.isFalling()) {
            checkLines();
            gameOver = checkGameOver();
            createPiece();
        } else if (piece.isFalling()) {
            down = true;
            canDown = true;
            canRotate = true;
        }
    }
    return gameOver;
}
void Tetris::draw(RenderWindow *win) {

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {

            if (!board[i][j]) {
                background[i][j].setFillColor(Color(255, 255, 255, 0));
                background[i][j].setOutlineColor(Color(164, 164, 164, 150));
            }

        }
    }


    for (int i = 0; i < 3; ++i) {
        nextPiece[i].draw(win);
    }

    for (int i = 0, k = 1; i < 4; ++i) {
        for (int j = 0; j < 4; ++j, k <<= 1) {
            if ((piece.getType() & k) == k) {

                background[piece.getY() + i][piece.getX() + j].setFillColor(piece.getColor());
                background[piece.getY() + i][piece.getX() + j].setOutlineColor(Color(255, 255, 255, 255));

            }
        }
    }

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            win->draw(background[i][j]);
        }
    }

}
void Tetris::drawEnemy(sf::RenderWindow *win, bool **enemy) {

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {

            if (!enemy[i][j]) {
                background[i][j].setFillColor(Color(255, 255, 255, 0));
                background[i][j].setOutlineColor(Color(164, 164, 164, 150));
            }

        }
    }

}

void Tetris::init() {

    clock.restart();
    lastTime = clock.getElapsedTime();

    score = 0;
    lines = 0;
    level = 0;
    speed = 1.0;

    board = new bool*[HEIGHT];
    for (int i = 0; i < HEIGHT; ++i) {
        board[i] = new bool[WIDTH];
        for (int j = 0; j < WIDTH; ++j) {

            board[i][j] = false;

        }
    }

    background = new RectangleShape*[HEIGHT];
    for (int i = 0; i < HEIGHT; ++i) {
        background[i] = new RectangleShape[WIDTH];
        for (int j = 0; j < WIDTH; ++j) {
            background[i][j] = RectangleShape(Vector2f(FIELD_SIZE, FIELD_SIZE));
            background[i][j].setFillColor(Color(255, 255, 255, 0));
            background[i][j].setOutlineColor(Color(164, 164, 164, 150));
            background[i][j].setOutlineThickness(1);
            background[i][j].setPosition(j * FIELD_SIZE + 2 * j + 1,i * FIELD_SIZE + 2 * i + 1);
        }

    }

    piece = Piece();
    piece.setY(piece.getY() - piece.furthestUp());

    nextPiece = new Piece[3];
    for (int i = 0; i < 3; ++i) {
        nextPiece[i] = Piece(6 + (i * 5), 5, false);
        nextPiece[i].setSize(10, 10);
    }
                       

}

void Tetris::createPiece() {

    left = false;
    right = false;
    down = false;
    rotate = false;
    canDown = false;
    canRotate = false;

    piece = nextPiece[0];
    piece.setFalling(true);
    piece.setX(4);
    piece.setY(piece.getY() - piece.furthestUp());
    piece.setSize(FIELD_SIZE, FIELD_SIZE);

    for (int i = 0; i < 2; ++i) {
        nextPiece[i] = nextPiece[i + 1];
        nextPiece[i].setX(6 + (i * 5));
    }

    nextPiece[2] = Piece(6 + (2 * 5), 5, false);
    nextPiece[2].setSize(10, 10);

}
void Tetris::checkLines() {

    int lastLine = lines;

    for (int i = HEIGHT - 1; i >= 0; --i) {
        bool full = true;
        for (int j = 0; j < WIDTH; ++j) {

            if (!board[i][j]) {
                full = false;
                break;
            }

        }
        if (full) {
            ++lines;
            for(int j = i; j > 0; --j){
                for (int k = 0; k < WIDTH; ++k) {
                    board[j][k] = board[j - 1][k];
                    background[j][k].setFillColor(background[j - 1][k].getFillColor());
                    background[j][k].setOutlineColor(background[j - 1][k].getOutlineColor());
                }
            }
            ++i;
        }
    }

    if (lines % 10 == 0 && lines > 0 && lines != lastLine) {
        ++level;
        speed -= 0.1;
    }
}

bool Tetris::checkGameOver() {

    for (int i = 0; i < WIDTH; ++i) {
        if (board[0][i]) {
            cout << "Game Over" << endl;
            return true;
        }
    }

    return false;

}
void Tetris::movePiece() {


    if (piece.isFalling()) {
        if (left) {
            bool canLeft = false;
            for (int i = 0; i < 4; ++i) {
                if (piece.getY() + i > 0 && piece.furthestLeft() > 0) {
                    if (!board[piece.getY() + i][piece.furthestLeft() - 1]) {
                        canLeft = true;
                    }
                }
            }
            if (canLeft) {
                piece.setX(piece.getX() - 1);
            }
        }
            if (right) {
                bool canRight = false;
                for (int i = 0; i < 4; ++i) {
                    if (piece.getY() + i > 0 && piece.furthestRight() > 0 && piece.furthestRight() < WIDTH - 1 &&
                        !board[piece.getY() + i][piece.furthestRight() + 1]) {
                        canRight = true;
                    }
                }
                if (canRight) {
                    piece.setX(piece.getX() + 1);
                }
            }
            if (down && canDown) {
                if (piece.furthestDown() < HEIGHT - 1) {
                    piece.setY(piece.getY() + 1);
                }
            }
            if (rotate && canRotate) {
                piece.rotate();
                if (piece.furthestLeft() < 0) {
                    piece.setX(0);
                } else if (piece.furthestRight() > WIDTH - 1) {
                    piece.setX(WIDTH - 4);
                }

            }
        }

        left = false;
        right = false;
        down = false;
        rotate = false;

        piece.setFalling(piece.checkBelow(board));


        for (int i = 0, k = 1; i < 4; ++i) {
            for (int j = 0; j < 4; ++j, k <<= 1) {
                if ((piece.getType() & k) == k && !piece.isFalling()) {
                    board[piece.getY() + i][piece.getX() + j] = true;
                    background[piece.getY() + i][piece.getX() + j].setFillColor(piece.getColor());
                    background[piece.getY() + i][piece.getX() + j].setOutlineColor(Color(255, 255, 255, 255));
                }
            }
        }

    }
void Tetris::savePiece() {

    if (holdPiece != nullptr) {

        *holdPiece = piece;cout << "Hold Piece: " << endl;
        createPiece();
    } else {
        Piece temp = piece;
        piece = *holdPiece;
        *holdPiece = temp;
    }

}


