//
// Created by LeoNora on 15.01.2024.
//

#include "../../include/window.h"


window::window() {

    VideoMode desktop = VideoMode().getDesktopMode();
//    WINDOW_WIDTH = desktop.width;
//    WINDOW_HEIGHT = desktop.height;

    normal = VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
    multi = VideoMode(WINDOW_WIDTH * 2, WINDOW_HEIGHT);
    this->win = new RenderWindow(multi, "Tetris", Style::Close);

    this->status = MENU;
    this->mp_status = NONE;

    init();

    start();

}

window::~window() {

//    delete this->win;
//    delete this->tetris;

}

void window::init() {

    server = new NetworkHandler();

    singlePlayer_Button = RectangleShape(Vector2f(200, 50));
    singlePlayer_Button.setFillColor(Color(255, 255, 255, 255));
    singlePlayer_Button.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 100));
    singlePlayer_Button.setOutlineColor(Color(164, 164, 164, 255));
    singlePlayer_Button.setOutlineThickness(5);

    multiPlayer_Button = RectangleShape(Vector2f(200, 50));
    multiPlayer_Button.setFillColor(Color(255, 255, 255, 255));
    multiPlayer_Button.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2));
    multiPlayer_Button.setOutlineColor(Color(164, 164, 164, 255));
    multiPlayer_Button.setOutlineThickness(5);

    exit_Button = RectangleShape(Vector2f(200, 50));
    exit_Button.setFillColor(Color(255, 255, 255, 255));
    exit_Button.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 100));
    exit_Button.setOutlineColor(Color(164, 164, 164, 255));
    exit_Button.setOutlineThickness(5);

    host_Button = RectangleShape(Vector2f(200, 50));
    host_Button.setFillColor(Color(255, 255, 255, 255));
    host_Button.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100, 100));
    host_Button.setOutlineColor(Color(164, 164, 164, 255));
    host_Button.setOutlineThickness(5);

    join_Button = RectangleShape(Vector2f(200, 50));
    join_Button.setFillColor(Color(255, 255, 255, 255));
    join_Button.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100, 200));
    join_Button.setOutlineColor(Color(164, 164, 164, 255));
    join_Button.setOutlineThickness(5);

    exit_Button_Multiplayer = RectangleShape(Vector2f(200, 50));
    exit_Button_Multiplayer.setFillColor(Color(255, 255, 255, 255));
    exit_Button_Multiplayer.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100, 300));
    exit_Button_Multiplayer.setOutlineColor(Color(164, 164, 164, 255));
    exit_Button_Multiplayer.setOutlineThickness(5);

    resume_Button = RectangleShape(Vector2f(200, 50));
    resume_Button.setFillColor(Color(255, 255, 255, 255));
    resume_Button.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 100));
    resume_Button.setOutlineColor(Color(164, 164, 164, 255));
    resume_Button.setOutlineThickness(5);

    restart_Button = RectangleShape(Vector2f(200, 50));
    restart_Button.setFillColor(Color(255, 255, 255, 255));
    restart_Button.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2));
    restart_Button.setOutlineColor(Color(164, 164, 164, 255));
    restart_Button.setOutlineThickness(5);

    mainMenu_Button = RectangleShape(Vector2f(200, 50));
    mainMenu_Button.setFillColor(Color(255, 255, 255, 255));
    mainMenu_Button.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 100));
    mainMenu_Button.setOutlineColor(Color(164, 164, 164, 255));
    mainMenu_Button.setOutlineThickness(5);

    exit_Button_Pause = RectangleShape(Vector2f(200, 50));
    exit_Button_Pause.setFillColor(Color(255, 255, 255, 255));
    exit_Button_Pause.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 200));
    exit_Button_Pause.setOutlineColor(Color(164, 164, 164, 255));
    exit_Button_Pause.setOutlineThickness(5);

    retry_Button = RectangleShape(Vector2f(200, 50));
    retry_Button.setFillColor(Color(255, 255, 255, 255));
    retry_Button.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2));
    retry_Button.setOutlineColor(Color(164, 164, 164, 255));
    retry_Button.setOutlineThickness(5);

    mainMenu_Button = RectangleShape(Vector2f(200, 50));
    mainMenu_Button.setFillColor(Color(255, 255, 255, 255));
    mainMenu_Button.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 100));
    mainMenu_Button.setOutlineColor(Color(164, 164, 164, 255));
    mainMenu_Button.setOutlineThickness(5);

    font.loadFromFile("Mono.ttf");

    singlePlayer_Text = Text("Single Player", font, 20);
    singlePlayer_Text.setFillColor(Color::Black);
    singlePlayer_Text.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100 + 30, WINDOW_HEIGHT / 2 - 100 + 5));

    multiPlayer_Text = Text("Multi Player", font, 20);
    multiPlayer_Text.setFillColor(Color::Black);
    multiPlayer_Text.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100 + 30, WINDOW_HEIGHT / 2 + 5));

    exit_Text = Text("Exit", font, 20);
    exit_Text.setFillColor(Color::Black);
    exit_Text.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100 + 30, WINDOW_HEIGHT / 2 + 100 + 5));

    resume_Text = Text("Resume", font, 20);
    resume_Text.setFillColor(Color::Black);
    resume_Text.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100 + 30, WINDOW_HEIGHT / 2 - 100 + 5));

    restart_Text = Text("Restart", font, 20);
    restart_Text.setFillColor(Color::Black);
    restart_Text.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100 + 30, WINDOW_HEIGHT / 2 + 5));

    mainMenu_Text = Text("Main Menu", font, 20);
    mainMenu_Text.setFillColor(Color::Black);
    mainMenu_Text.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100 + 30, WINDOW_HEIGHT / 2 + 100 + 5));

    host_Text = Text("Host", font, 20);
    host_Text.setFillColor(Color::Black);
    host_Text.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100 + 30, 100 + 5));

    join_Text = Text("Join", font, 20);
    join_Text.setFillColor(Color::Black);
    join_Text.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100 + 30, 200 + 5));

    exit_Text_Multiplayer = Text("Exit", font, 20);
    exit_Text_Multiplayer.setFillColor(Color::Black);
    exit_Text_Multiplayer.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100 + 30, 300 + 5));

    exit_Text_Pause = Text("Exit", font, 20);
    exit_Text_Pause.setFillColor(Color::Black);
    exit_Text_Pause.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100 + 30, WINDOW_HEIGHT / 2 + 200 + 5));

    gameOver_Text = Text("Game Over", font, 20);
    gameOver_Text.setFillColor(Color::White);
    gameOver_Text.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 100));

    retry_Text = Text("Retry", font, 20);
    retry_Text.setFillColor(Color::Black);
    retry_Text.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100 + 30, WINDOW_HEIGHT / 2 + 5));

    mainMenu_Text = Text("Main Menu", font, 20);
    mainMenu_Text.setFillColor(Color::Black);
    mainMenu_Text.setPosition(Vector2f(WINDOW_WIDTH / 2 - 100 + 30, WINDOW_HEIGHT / 2 + 100 + 5));

}


void window::start() {

    while (this->win->isOpen()) {

        while (this->status == MENU && this->win->isOpen()) {
            updateMenu();
            renderMenu();
        }

        while (this->status == S_PLAYER && this->win->isOpen()) {
            updateGame();
            renderGame();
        }

        while (this->status == M_PLAYER && this->win->isOpen()) {
            updateMultiplayerMenu();
            renderMultiplayerMenu();
            while ((this->mp_status == HOST || this->mp_status == CLIENT) && this->win->isOpen()) {
                updateMultiplayer();
                renderMultiplayer();
            }
        }

        while (this->status == PAUSE && this->win->isOpen()) {
            updatePause();
            renderPause();
        }

        while (this->status == GAME_OVER && this->win->isOpen()) {
            updateGameOver();
            renderGameOver();
        }

    }

    cout << "window closed" << endl;
    exit(0);

}

void window::updateMenu() {


    Event event;
    while (this->win->pollEvent(event)) {
        if (event.type == Event::Closed) {
            this->win->close();
        }
    }

    Vector2i mousePos = Mouse::getPosition(*win);
    FloatRect singlePlayer_bounds = singlePlayer_Button.getGlobalBounds();
    FloatRect multiPlayer_bounds = multiPlayer_Button.getGlobalBounds();
    FloatRect exit_bounds = exit_Button.getGlobalBounds();

    if (singlePlayer_bounds.contains(static_cast<Vector2f>(mousePos))) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            status = S_PLAYER;
            win->setSize(Vector2u(static_cast<unsigned int>(WINDOW_WIDTH), static_cast<unsigned int>(WINDOW_HEIGHT)));
            this->tetris = new Tetris(WINDOW_WIDTH, WINDOW_HEIGHT);
        }
    }
    if (multiPlayer_bounds.contains(static_cast<Vector2f>(mousePos))) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            status = status::M_PLAYER;
            win->setSize(Vector2u(static_cast<unsigned int>(WINDOW_WIDTH * 2), static_cast<unsigned int>(WINDOW_HEIGHT)));
            this->tetris = new Tetris(WINDOW_WIDTH * 2, WINDOW_HEIGHT, MODE::MULTIPLAYER);
        }
    }
    if (exit_bounds.contains(static_cast<Vector2f>(mousePos))) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            this->win->close();
        }
    }
    if (event.type == Event::Resized) {
        FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        win->setView(View(visibleArea));
    }

}
void window::renderMenu() {

    this->win->clear(Color::Black);

    this->win->draw(singlePlayer_Button);
    this->win->draw(multiPlayer_Button);
    this->win->draw(exit_Button);

    this->win->draw(singlePlayer_Text);
    this->win->draw(multiPlayer_Text);
    this->win->draw(exit_Text);

    this->win->display();

}
void window::updateMultiplayerMenu() {

    Event event;
    while (this->win->pollEvent(event)) {
        if (event.type == Event::Closed) {
            this->win->close();
        }
    }

    Vector2i mousePos = Mouse::getPosition(*win);
    FloatRect host_bounds = host_Button.getGlobalBounds();
    FloatRect join_bounds = join_Button.getGlobalBounds();
    FloatRect exit_bounds = exit_Button_Multiplayer.getGlobalBounds();

    if (host_bounds.contains(static_cast<Vector2f>(mousePos))) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            cout << "HOST" << endl;
            mp_status = HOST;
            server->connectServer(65000);
        }
    }
    if (join_bounds.contains(static_cast<Vector2f>(mousePos))) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            cout << "CLIENT" << endl;
            mp_status = CLIENT;
//            IpAddress serverAddress = "172.16.163.136";
            IpAddress serverAddress = IpAddress::getLocalAddress();
            server->connectClient(65000, serverAddress);
        }
    }
    if (exit_bounds.contains(static_cast<Vector2f>(mousePos))) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            this->win->close();
        }
    }
}
void window::renderMultiplayerMenu() {

    this->win->clear(Color::Black);

    this->win->draw(host_Button);
    this->win->draw(join_Button);
    this->win->draw(exit_Button_Multiplayer);

    this->win->draw(host_Text);
    this->win->draw(join_Text);
    this->win->draw(exit_Text_Multiplayer);

    this->win->display();

}
void window::updateGame() {

    if (tetris->update()) {
        status = GAME_OVER;
    }

    Event event;
    while (this->win->pollEvent(event)) {

        if (event.type == Event::Closed) {
            this->win->close();
        }
        if (event.type == Event::MouseButtonPressed) {

            if (event.mouseButton.button == Mouse::Left) {

            }

        }
        if (event.type == Event::KeyPressed) {

            if (event.key.code == Keyboard::Left || event.key.code == Keyboard::A) {
                tetris->setLeft(true);
            }
            if (event.key.code == Keyboard::Right || event.key.code == Keyboard::D) {
                tetris->setRight(true);
            }
            if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S) {
                tetris->setDown(true);
            }
            if (event.key.code == Keyboard::Up || event.key.code == Keyboard::W) {
                tetris->setRotate(true);
            }
            if (event.key.code == Keyboard::E) {
                tetris->savePiece();
            }
            if (event.key.code == Keyboard::Escape) {
                status = PAUSE;
            }
            tetris->movePiece();

        }

    }

}
void window::renderGame() {

    this->win->clear(Color::Black);

    RectangleShape *background_NextPiece = new RectangleShape;
    background_NextPiece->setSize(Vector2f(190, HEIGHT * FIELD_SIZE + 30));
    background_NextPiece->setFillColor(Color(255, 255, 255, 200));
    background_NextPiece->setPosition(Vector2f(tetris->getBackground()[0][WIDTH - 1].getGlobalBounds().left + tetris->getBackground()[0][WIDTH - 1].getGlobalBounds().width + 6, tetris->getBackground()[0][0].getGlobalBounds().top + 5));
    background_NextPiece->setOutlineColor(Color(164, 164, 164, 255));
    background_NextPiece->setOutlineThickness(5);

    Text nextPiece_Text = Text("Next Pieces: ", font, 17);
    nextPiece_Text.setFillColor(Color::Black);
    nextPiece_Text.setPosition(Vector2f(WINDOW_WIDTH - 190, 10));

    Text lines_Text = Text("Lines: " + to_string(tetris->getLines()), font, 17);
    lines_Text.setFillColor(Color::Black);
    lines_Text.setPosition(Vector2f(WINDOW_WIDTH - 190, 100));


    this->win->draw(*background_NextPiece);
    this->win->draw(nextPiece_Text);
    this->win->draw(lines_Text);


    tetris->draw(this->win);


    this->win->display();

    delete background_NextPiece;

}
void window::updateMultiplayer() {

    if (tetris->update()) {
        status = GAME_OVER;
    }

    Event event;
    while (this->win->pollEvent(event)) {

        if (event.type == Event::Closed) {
            this->win->close();
        }
        if (event.type == Event::MouseButtonPressed) {

            if (event.mouseButton.button == Mouse::Left) {

            }

        }
        if (event.type == Event::KeyPressed) {

            if (event.key.code == Keyboard::Left || event.key.code == Keyboard::A) {
                tetris->setLeft(true);
            }
            if (event.key.code == Keyboard::Right || event.key.code == Keyboard::D) {
                tetris->setRight(true);
            }
            if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S) {
                tetris->setDown(true);
            }
            if (event.key.code == Keyboard::Up || event.key.code == Keyboard::W) {
                tetris->setRotate(true);
            }
            if (event.key.code == Keyboard::Escape) {
                status = PAUSE;
            }
            tetris->movePiece();

        }


    }

    **enemyBoard = new bool * [20];
    for (int i = 0; i < 20; ++i) {
        enemyBoard[i] = new bool [10];
    }

    if (mp_status == HOST) {
        enemyBoard = server->send(tetris->getBoardAll());

    } else if (mp_status == CLIENT) {
        enemyBoard = server->send(tetris->getBoardAll());
    }

    cout << "NEW DRAW" << endl;
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 10; ++j) {
            cout << enemyBoard[i][j] << " ";
        }
        cout << endl;
    }





}
void window::renderMultiplayer() {

    this->win->clear(Color::Black);

    RectangleShape *background_NextPiece = new RectangleShape;
    background_NextPiece->setSize(Vector2f(190, WINDOW_HEIGHT - 10));
    background_NextPiece->setFillColor(Color(255, 255, 255, 200));
    background_NextPiece->setPosition(Vector2f(WINDOW_WIDTH - 195, 5));
    background_NextPiece->setOutlineColor(Color(164, 164, 164, 255));
    background_NextPiece->setOutlineThickness(5);

    Text nextPiece_Text = Text("Next Pieces: ", font, 17);
    nextPiece_Text.setFillColor(Color::Black);
    nextPiece_Text.setPosition(Vector2f(WINDOW_WIDTH - 190, 10));

    Text lines_Text = Text("Lines: " + to_string(tetris->getLines()), font, 17);
    lines_Text.setFillColor(Color::Black);
    lines_Text.setPosition(Vector2f(WINDOW_WIDTH - 190, 100));


    this->win->draw(*background_NextPiece);
    this->win->draw(nextPiece_Text);
    this->win->draw(lines_Text);


    tetris->draw(this->win);


    this->win->display();

    delete background_NextPiece;

}
void window::updatePause() {

    Event event;
    while (this->win->pollEvent(event)) {
        if (event.type == Event::Closed) {
            this->win->close();
        }
    }

    Vector2i mousePos = Mouse::getPosition(*win);
    FloatRect resume_bounds = resume_Button.getGlobalBounds();
    FloatRect restart_bounds = restart_Button.getGlobalBounds();
    FloatRect mainMenu_bounds = mainMenu_Button.getGlobalBounds();
    FloatRect exit_bounds = exit_Button_Pause.getGlobalBounds();

    if (resume_bounds.contains(static_cast<Vector2f>(mousePos))) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            status = S_PLAYER;
        }
    }
    if (restart_bounds.contains(static_cast<Vector2f>(mousePos))) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            tetris->~Tetris();
            tetris = new Tetris(WINDOW_WIDTH, WINDOW_HEIGHT);
            status = S_PLAYER;
        }
    }
    if (mainMenu_bounds.contains(static_cast<Vector2f>(mousePos))) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            tetris->~Tetris();
            tetris = new Tetris(WINDOW_WIDTH, WINDOW_HEIGHT);
            status = MENU;
        }
    }
    if (exit_bounds.contains(static_cast<Vector2f>(mousePos))) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            this->win->close();
        }
    }


}
void window::renderPause() {

    this->win->clear(Color::Black);

    this->win->draw(resume_Button);
    this->win->draw(restart_Button);
    this->win->draw(mainMenu_Button);
    this->win->draw(exit_Button_Pause);

    this->win->draw(resume_Text);
    this->win->draw(restart_Text);
    this->win->draw(mainMenu_Text);
    this->win->draw(exit_Text_Pause);

    this->win->display();

}
void window::updateGameOver() {

    Event event;
    while (this->win->pollEvent(event)) {
        if (event.type == Event::Closed) {
            this->win->close();
        }
    }

    Vector2i mousePos = Mouse::getPosition(*win);
    FloatRect retry_bounds = retry_Button.getGlobalBounds();
    FloatRect mainMenu_bounds = mainMenu_Button.getGlobalBounds();

    if (retry_bounds.contains(static_cast<Vector2f>(mousePos))) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            tetris->~Tetris();
            tetris = new Tetris(WINDOW_WIDTH, WINDOW_HEIGHT);
            status = S_PLAYER;
        }
    }
    if (mainMenu_bounds.contains(static_cast<Vector2f>(mousePos))) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
            tetris->~Tetris();
            tetris = new Tetris(WINDOW_WIDTH, WINDOW_HEIGHT);
            status = MENU;
        }
    }


}
void window::renderGameOver() {

    this->win->clear(Color::Black);

    this->win->draw(gameOver_Text);
    this->win->draw(retry_Button);
    this->win->draw(mainMenu_Button);
    this->win->draw(retry_Text);
    this->win->draw(mainMenu_Text);

    this->win->display();

}