//
// Created by Ashley on 17.04.2024.
//

#ifndef TETRIS_SERVER_H
#define TETRIS_SERVER_H

#include <iostream>
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
    void transmit(char *message);
    char * receive();

    TcpListener listener;
    TcpSocket socket;
    SocketSelector selector;

    list<TcpSocket *> clients;

};


#endif //TETRIS_SERVER_H