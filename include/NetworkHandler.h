//
// Created by Ashley on 18.02.2024.
//

#ifndef TETRIS_NETWORKHANDLER_H
#define TETRIS_NETWORKHANDLER_H

#include "SFML/Network.hpp"

using namespace sf;

class NetworkHandler {
public:

    void start();
    void connectServer(unsigned short port);
    void connectClient(unsigned short port, IpAddress serverAddress);
    bool ** send(bool **data);
    void transmitGameOver(bool gameOver);
    bool receiveGameOver();

private:

    TcpListener listener;
    TcpSocket socket;
    unsigned short port;

};

#endif //TETRIS_NETWORKHANDLER_H
