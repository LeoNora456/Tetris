//
// Created by LeoNora on 15.01.2024.
//

#ifndef TETRIS_WINDOW_H
#define TETRIS_WINDOW_H

#include <iostream>
#include <ctime>
#include <functional>

#include "SFML/Graphics.hpp"

#include "Piece.h"
#include "Tetris.h"
#include "NetworkHandler.h"
#include "Server.h"
#include "Client.h"

#define GAME_WIDTH (FIELD_SIZE * WIDTH + 220)
#define GAME_HEIGHT (FIELD_SIZE * HEIGHT + 40)

#define FPS 60
#define TPS 60

using namespace std;
using namespace sf;

enum status {
    MENU,
    S_PLAYER,
    M_PLAYER,
    CONNECTING,
    PAUSE,
    GAME_OVER
};
enum mp_status {
    HOST,
    CLIENT,
    NONE
};

class window {

public:

    window();
    ~window();

private:


    void init();
    void start();
    void updateMenu();
    void renderMenu();
    void updateMultiplayerMenu();
    void renderMultiplayerMenu();
    void updateWaitForClients();
    void renderWaitForClients();
    void updateGame();
    void renderGame();
    void updateMultiplayer();
    void renderMultiplayer();
    void updatePause();
    void renderPause();
    void updateGameOver();
    void renderGameOver();

    void changeWindowSize();


    bool **enemyBoard;
    RectangleShape **enemyBackground;

    VideoMode normal, multi;

    RenderWindow *win;
    Tetris *tetris;
    status status;
    mp_status mp_status;

    // NETWORK
    Server *server;
    Client *client;

    // BUTTONS
    RectangleShape singlePlayer_Button, multiPlayer_Button, exit_Button;
    RectangleShape host_Button, join_Button, exit_Button_Multiplayer, start_Multiplayer_Button;
    RectangleShape resume_Button, restart_Button, mainMenu_Button, exit_Button_Pause;
    RectangleShape retry_Button, mainMenu_Button_GameOver;

    // TEXT
    Font font;
    Text singlePlayer_Text, multiPlayer_Text, exit_Text;
    Text host_Text, join_Text, exit_Text_Multiplayer, start_Multiplayer_Text;
    Text resume_Text, restart_Text, mainMenu_Text, exit_Text_Pause;
    Text retry_Text, mainMenu_Text_GameOver, gameOver_Text;


};

#endif //TETRIS_WINDOW_H
