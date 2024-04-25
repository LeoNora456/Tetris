//
// Created by Ashley on 17.04.2024.
//

#include "../../include/Server.h"

void Server::connect(unsigned short port) {

    listener.setBlocking(false);
    listener.listen(port);

    socket.setBlocking(false);

    listener.accept(socket);

//    selector.add(listener);
//    selector.add(socket);


}

void Server::waitForClients() {

//    if (selector.wait(milliseconds(100))) {
//        if (selector.isReady(listener)) {

            if (listener.accept(client) == sf::Socket::Done) {
                selector.add(client);
                cout << "Client connected" << endl;
            }
//        }
//    }

}


bool ** Server::send(bool **data) {

    Socket::Status status;

    Packet sendPacket, receivePacket;
    for (unsigned int i = 0; i < 20; i++) {
        for (unsigned int j = 0; j < 10; j++) {
            sendPacket << data[i][j];
        }
    }
    client.send(sendPacket);
    status = client.receive(receivePacket);

    if (status != sf::Socket::Done) {
        return nullptr;
    }

    bool **receivedData = new bool*[20];
    for (unsigned int i = 0; i < 20; i++) {
        receivedData[i] = new bool[10];
        for (unsigned int j = 0; j < 10; j++) {
            receivePacket >> receivedData[i][j];
        }
    }

    return receivedData;

}

void Server::transmit(char *message) {

    Packet sendPacket;
    for (int i = 0; i < sizeof(message); i++) {
        sendPacket << message[i];
    }

    Socket::Status sendStatus = client.send(sendPacket);
    if (sendStatus == sf::Socket::Done) {
        cout << "Transmitted message: " << message << endl;
    } else {
        cerr << "Failed to send message" << endl;
    }

}
char * Server::receive() {

    Packet receivePacket;
    char *message = new char[100];

    if (socket.receive(receivePacket) != sf::Socket::Done) {
        return nullptr;
    } else {
        cout << "Received message: ";
    }


    for (int i = 0; i < 100; ++i) {
        receivePacket >> message;
    }

    cout << message[0] << endl;

    return message;

}