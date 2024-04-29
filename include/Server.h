//
// Created by Ashley on 17.04.2024.
//

#ifndef TETRIS_SERVER_H
#define TETRIS_SERVER_H

#include <iostream>
#include <string.h>
#include <iomanip>
#include <optional>
#include <list>

#include "SFML/Network.hpp"

using namespace sf;
using namespace std;

class Server {
public:
    void connect(unsigned short port);
    void waitForClients();
    bool ** send(bool **data);
    void transmit(char *message);
    char * receive();

    TcpListener listener;
    TcpSocket socket;
    SocketSelector selector;

    TcpSocket client;

};


#endif //TETRIS_SERVER_H
