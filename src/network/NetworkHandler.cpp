//
// Created by Ashley on 18.02.2024.
//

#include "../../include/NetworkHandler.h"

void NetworkHandler::connectServer(unsigned short port) {

    listener.setBlocking(false);
    listener.listen(port);

    socket.setBlocking(false);

    listener.accept(socket);

    selector.add(listener);
    selector.add(socket);

}
void NetworkHandler::connectClient(unsigned short port, IpAddress serverAddress) {

    socket.setBlocking(false);
    socket.connect(serverAddress, port);

}
bool NetworkHandler::waitForClients() {

    if (selector.wait(milliseconds(100))) {
        if (selector.isReady(listener)) {

            if (listener.accept(client) == sf::Socket::Done) {
                selector.add(client);
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
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
void NetworkHandler::transmitGameStarted(bool gameStarted) {

    Packet sendPacket;
    sendPacket << gameStarted;



    Socket::Status sendStatus = socket.send(sendPacket);
    if (sendStatus == sf::Socket::Done) {
        std::cout << "Game started status transmitted successfully\n";
    } else if (sendStatus == sf::Socket::Partial) {
        std::cerr << "Partial send occurred. Data might not have been fully transmitted\n";
    } else if (sendStatus == Socket::Error) {
        std::cerr << "Failed to transmit gameStarted packet. Error code: " << sendStatus << std::endl;
    }

}
bool NetworkHandler::receiveGameStarted() {

    Packet receivePacket;
    bool gameStarted;

    if (socket.receive(receivePacket) != sf::Socket::Done) {
        cerr << "Failed to receive gameStarted packet\n";
        return false;
    }

    receivePacket.clear();

    if (receivePacket >> gameStarted) {
        return gameStarted;
    } else {
        cerr << "Failed to read gameStarted from packet\n";
        return false;
    }


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