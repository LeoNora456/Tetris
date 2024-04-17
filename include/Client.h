//
// Created by Ashley on 17.04.2024.
//

#ifndef TETRIS_CLIENT_H
#define TETRIS_CLIENT_H

#include <iostream>
#include <iomanip>
#include <optional>

#include "SFML/Network.hpp"

using namespace sf;
using namespace std;

class Client {
public:
    void connect(unsigned short port, IpAddress serverAddress);
    void transmit(char *message);
    char * receive();

    TcpSocket socket;

};


#endif //TETRIS_CLIENT_H
