//
// Created by Ashley on 18.02.2024.
//

#ifndef TETRIS_NETWORKHANDLER_H
#define TETRIS_NETWORKHANDLER_H

#include <iostream>
#include <iomanip>
#include <optional>

#include "SFML/Network.hpp"

using namespace sf;
using namespace std;

class NetworkHandler {
public:

    void start();
    void connectServer(unsigned short port);
    void connectClient(unsigned short port, IpAddress serverAddress);
    void waitForClients();
    bool ** send(bool **data);
    void transmitGameOver(bool gameOver);
    bool receiveGameOver();

private:

    TcpListener listener;
    SocketSelector selector;
    TcpSocket socket, client;
    unsigned short port;

};

#endif //TETRIS_NETWORKHANDLER_H
