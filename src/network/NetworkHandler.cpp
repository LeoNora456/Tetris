//
// Created by Ashley on 18.02.2024.
//

#include "../../include/NetworkHandler.h"

void NetworkHandler::connectServer(unsigned short port) {

    listener.listen(port);
    bool connected = false;
    while (!connected) {
        if (listener.accept(socket) == Socket::Done) {
            connected = true;
        }
    }

}
void NetworkHandler::connectClient(unsigned short port, IpAddress serverAddress) {

    socket.connect(serverAddress, port);


//    Socket::Status status = socket.connect(serverAddress, port);
//    if (status != Socket::Done) {
//
//    }

}
bool ** NetworkHandler::send(bool **data) {

    Packet sendPacket, receivePacket;
    for (unsigned int i = 0; i < 20; i++) {
        for (unsigned int j = 0; j < 10; j++) {
            sendPacket << data[i][j];
        }
    }
    socket.send(sendPacket);
    socket.receive(receivePacket);

    bool **receivedData = new bool*[20];
    for (unsigned int i = 0; i < 20; i++) {
        receivedData[i] = new bool[10];
        for (unsigned int j = 0; j < 10; j++) {
            receivePacket >> receivedData[i][j];
        }
    }

    return receivedData;

}
void NetworkHandler::transmitGameOver(bool gameOver) {

    Packet sendPacket;
    sendPacket << gameOver;
    socket.send(sendPacket);

}
bool NetworkHandler::receiveGameOver() {

    Packet receivePacket;
    bool gameOver;
    socket.receive(receivePacket);
    receivePacket >> gameOver;

    return gameOver;

}