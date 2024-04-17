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

    socket.setBlocking(true);
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
void NetworkHandler::transmit(char *message) {

    Packet sendPacket;
    for (int i = 0; i < sizeof(message); i++) {
        sendPacket << message[i];
    }

    Socket::Status sendStatus = client.send(sendPacket);
    if (sendStatus == sf::Socket::Done) {
        std::cout << "Game started status transmitted successfully\n";
    } else if (sendStatus == sf::Socket::Partial) {
        std::cerr << "Partial send occurred. Data might not have been fully transmitted\n";
    } else if (sendStatus == Socket::Error) {
        std::cerr << "Failed to transmit gameStarted packet. Error code: " << sendStatus << std::endl;
    }

}
char * NetworkHandler::receive() {

    Packet receivePacket;
    char *message = new char[100];

    if (socket.receive(receivePacket) != sf::Socket::Done) {
        cerr << "Failed to receive gameStarted packet\n";
    }


    for (int i = 0; i < 100; ++i) {
        receivePacket >> message;
    }

    return message;


}
