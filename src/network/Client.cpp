//
// Created by Ashley on 17.04.2024.
//

#include "../../include/Client.h"

void Client::connect(unsigned short port, IpAddress serverAddress) {

    socket.setBlocking(false);
    socket.connect(serverAddress, port);

}

void Client::transmit(char *message) {

    Packet packet;
    packet << message;
    socket.send(packet);

}
char * Client::receive() {

    Packet packet;
    socket.receive(packet);

    char *message;
    packet >> message;

    return message;

}