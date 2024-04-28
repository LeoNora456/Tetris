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

    currentTime = clock.getElapsedTime();
    Time diff = currentTime - lastTime;
    double timePassed = diff.asMilliseconds();

    if (timePassed >= 1000 * speed) {

        lastTime = currentTime;
        if (piece.getLocked()) {

            updateStats();
            checkLines();
            gameOver = checkGameOver();
            createPiece();

        } else {
            down = true;
            canDown = true;
            canRotate = true;
            movePiece();
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
    if (holdPiece != nullptr) {
        holdPiece->draw(win);
    }

    Color temp = piece_copy.getColor();
    temp.a = 50;
    piece_copy.setColor(temp);

    example_I.draw(win);
    example_O.draw(win);
    example_T.draw(win);
    example_S.draw(win);
    example_Z.draw(win);
    example_J.draw(win);
    example_L.draw(win);

    Text I_text("-> " + to_string(I), font, 20);
    I_text.setFillColor(Color::White);
    I_text.setPosition(GAME_WIDTH - 90, 210);
    Text O_text("-> " + to_string(O), font, 20);
    O_text.setFillColor(Color::White);
    O_text.setPosition(GAME_WIDTH - 90, 260);
    Text T_text("-> " + to_string(T), font, 20);
    T_text.setFillColor(Color::White);
    T_text.setPosition(GAME_WIDTH - 90, 310);
    Text S_text("-> " + to_string(S), font, 20);
    S_text.setFillColor(Color::White);
    S_text.setPosition(GAME_WIDTH - 90, 360);
    Text Z_text("-> " + to_string(Z), font, 20);
    Z_text.setFillColor(Color::White);
    Z_text.setPosition(GAME_WIDTH - 90, 410);
    Text J_text("-> " + to_string(J), font, 20);
    J_text.setFillColor(Color::White);
    J_text.setPosition(GAME_WIDTH - 90, 460);
    Text L_text("-> " + to_string(L), font, 20);
    L_text.setFillColor(Color::White);
    L_text.setPosition(GAME_WIDTH - 90, 510);

    Text scoreText("Score: " + to_string(score), font, 17);
    scoreText.setFillColor(Color::Black);
    scoreText.setPosition(GAME_WIDTH - 190, 160);

    for (int i = 0, k = 1; i < 4; ++i) {
        for (int j = 0; j < 4; ++j, k <<= 1) {

            if ((piece_copy.getType() & k) == k) {

                background[piece_copy.getY() + i][piece_copy.getX() + j].setFillColor(piece_copy.getColor());
                background[piece_copy.getY() + i][piece_copy.getX() + j].setOutlineColor(Color(255, 255, 255, 50));

            }
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

    win->draw(I_text);
    win->draw(O_text);
    win->draw(T_text);
    win->draw(S_text);
    win->draw(Z_text);
    win->draw(J_text);
    win->draw(L_text);
    win->draw(scoreText);

}

void Tetris::drawEnemy(sf::RenderWindow *win, bool **enemy, RectangleShape **enemyBackground) {

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {

            enemyBackground[i][j].setFillColor(Color(255, 255, 255, 0));
            enemyBackground[i][j].setOutlineColor(Color(164, 164, 164, 150));

        }
    }

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {

            if (enemy[i][j]) {
                enemyBackground[i][j].setFillColor(Color(255, 255, 255));
                enemyBackground[i][j].setOutlineColor(Color(164, 164, 164, 150));
            }

        }
    }

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            win->draw(enemyBackground[i][j]);
        }
    }

}

void Tetris::init() {

    clock.restart();
    lastTime = clock.getElapsedTime();

    if (!font.loadFromFile("../../include/Mono.ttf")) {
        cout << "Error loading font" << endl;
    }

    score = 0;
    lines = 0;
    level = 0;
    speed = 1.0;

    board = new bool *[HEIGHT];
    for (int i = 0; i < HEIGHT; ++i) {
        board[i] = new bool[WIDTH];
        for (int j = 0; j < WIDTH; ++j) {

            board[i][j] = false;

        }
    }

    background = new RectangleShape *[HEIGHT];
    for (int i = 0; i < HEIGHT; ++i) {
        background[i] = new RectangleShape[WIDTH];
        for (int j = 0; j < WIDTH; ++j) {
            background[i][j] = RectangleShape(Vector2f(FIELD_SIZE, FIELD_SIZE));
            background[i][j].setFillColor(Color(255, 255, 255, 20));
            background[i][j].setOutlineColor(Color(164, 164, 164, 150));
            background[i][j].setOutlineThickness(1);
            background[i][j].setPosition(j * FIELD_SIZE + 2 * j + 1, i * FIELD_SIZE + 2 * i + 1);
        }

    }

    piece = Piece();
    piece.setY(piece.getY() - piece.furthestUp());

    piece_copy = Piece(piece);
    Color temp = piece_copy.getColor();
    temp.a = 100;
    piece_copy.setColor(temp);

    nextPiece = new Piece[3];
    for (int i = 0; i < 3; ++i) {
        nextPiece[i] = Piece(6 + (i * 5), 5, false);
        nextPiece[i].setSize(10, 10);
    }

    I = 0;
    O = 0;
    T = 0;
    S = 0;
    Z = 0;
    J = 0;
    L = 0;

    example_I = Piece(Type::I0, 8, 20, false);
    example_I.setColor(Color::Black);
    example_I.setSize(10, 10);
    example_O = Piece(Type::O, 8, 25, false);
    example_O.setColor(Color::Black);
    example_O.setSize(10, 10);
    example_T = Piece(Type::T0, 8, 30, false);
    example_T.setColor(Color::Black);
    example_T.setSize(10, 10);
    example_S = Piece(Type::S0, 8, 35, false);
    example_S.setColor(Color::Black);
    example_S.setSize(10, 10);
    example_Z = Piece(Type::Z0, 8, 40, false);
    example_Z.setColor(Color::Black);
    example_Z.setSize(10, 10);
    example_J = Piece(Type::J0, 8, 45, false);
    example_J.setColor(Color::Black);
    example_J.setSize(10, 10);
    example_L = Piece(Type::L0, 8, 50, false);
    example_L.setColor(Color::Black);
    example_L.setSize(10, 10);

    holdPiece = nullptr;

}

void Tetris::updateStats() {

    if (piece.getType() == Type::I0 || piece.getType() == Type::I90 || piece.getType() == Type::I180 || piece.getType() == Type::I270) {
        ++I;
    } else if (piece.getType() == Type::O) {
        ++O;
    } else if (piece.getType() == Type::T0 || piece.getType() == Type::T90 || piece.getType() == Type::T180 || piece.getType() == Type::T270) {
        ++T;
    } else if (piece.getType() == Type::S0 || piece.getType() == Type::S90 || piece.getType() == Type::S180 || piece.getType() == Type::S270) {
        ++S;
    } else if (piece.getType() == Type::Z0 || piece.getType() == Type::Z90 || piece.getType() == Type::Z180 || piece.getType() == Type::Z270) {
        ++Z;
    } else if (piece.getType() == Type::J0 || piece.getType() == Type::J90 || piece.getType() == Type::J180 || piece.getType() == Type::J270) {
        ++J;
    } else if (piece.getType() == Type::L0 || piece.getType() == Type::L90 || piece.getType() == Type::L180 || piece.getType() == Type::L270) {
        ++L;
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

    piece_copy = piece;
    Color temp = piece_copy.getColor();
    temp.a = 0;
    piece_copy.setColor(temp);

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
            for (int j = i; j > 0; --j) {
                for (int k = 0; k < WIDTH; ++k) {
                    board[j][k] = board[j - 1][k];
                    background[j][k].setFillColor(background[j - 1][k].getFillColor());
                    background[j][k].setOutlineColor(background[j - 1][k].getOutlineColor());
                }
            }
            ++i;
        }
    }

    if (lines - lastLine == 1) {
        score += 40 * (level + 1);
        backToBack = false;
    } else if (lines - lastLine == 2) {
        score += 100 * (level + 1);
        backToBack = false;
    } else if (lines - lastLine == 3) {
        score += 300 * (level + 1);
        backToBack = false;
    } else if (lines - lastLine == 4 && backToBack) {
        score += 1200 * (level + 1);
    } else if (lines - lastLine == 4) {
        score += 800;
        backToBack = true;
    } else {
        backToBack = false;
    }

    if (lines % (level + 1) * 10 == 0 && lines > 0 && lines != lastLine) {
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
        if (down && canDown) {
            if (piece.furthestDown() < HEIGHT - 1) {
                piece.setY(piece.getY() + 1);
            }
        }
        if (rotate && canRotate) {
            if (piece.getY() >= 0) {
                piece.rotate();
                if (piece.furthestLeft() < 0) {
                    piece.setX(0);
                } else if (piece.furthestRight() > WIDTH - 1) {
                    piece.setX(WIDTH - 4);
                }
            }

        }
    }
    if (!piece.getLocked()) {

        if (left) {
            bool canLeft = false;
            for (int i = 0; i < 4; ++i) {
                if (piece.furthestLeft() > 0 && piece.getY() + i <= HEIGHT - 1 && piece.getY() + i >= 0) {
                    if (!board[piece.getY() + i][piece.furthestLeft() - 1]) {
                        canLeft = true;
                    } else {
                        canLeft = false;
                        cout << "Can't move left" << endl;
                        break;
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
                if (piece.furthestRight() < WIDTH - 1 && piece.getY() + i <= HEIGHT - 1 && piece.getY() + i >= 0) {
                    if (!board[piece.getY() + i][piece.furthestRight() + 1]) {
                        canRight = true;
                    } else {
                        canRight = false;
                        cout << "Can't move right" << endl;
                        break;
                    }
                }
            }
            if (canRight) {
                piece.setX(piece.getX() + 1);
            }
        }
    }

    left = false;
    right = false;
    down = false;
    rotate = false;

    piece_copy = piece;

    while (piece_copy.furthestDown() < HEIGHT - 1 && piece_copy.checkBelow(board)) {
        piece_copy.setY(piece_copy.getY() + 1);
    }
    if (!piece.isFalling()) {
        piece.setLocked(true);
    }

    piece.setFalling(piece.checkBelow(board));


    for (int i = 0, k = 1; i < 4; ++i) {
        for (int j = 0; j < 4; ++j, k <<= 1) {
            if ((piece.getType() & k) == k && piece.getLocked()) {
                board[piece.getY() + i][piece.getX() + j] = true;
                background[piece.getY() + i][piece.getX() + j].setFillColor(piece.getColor());
                background[piece.getY() + i][piece.getX() + j].setOutlineColor(Color(255, 255, 255, 255));

            }
        }
    }



}
void Tetris::savePiece() {


    if (holdPiece == nullptr) {

        holdPiece = new Piece(piece);
        createPiece();

    } else {

        int x = piece.getX();
        int y = piece.getY();

        Piece temp = piece;
        piece = *holdPiece;
        *holdPiece = temp;

        piece.setX(x);
        piece.setY(y);

        if (piece.getY() < 0) {
            piece.setY(0);
        }
        if (piece.furthestLeft() < 0) {
            piece.setX(piece.getX() - piece.furthestLeft());
        } else if (piece.furthestRight() > WIDTH - 1) {
            piece.setX(piece.furthestRight() - piece.getWidth());
        }

    }

    holdPiece->setSize(10, 10);
    holdPiece->setX(11);
    holdPiece->setY(12);

}
void Tetris::putDown() {
    piece.setY(piece_copy.getY());
    piece.setLocked(true);
}
