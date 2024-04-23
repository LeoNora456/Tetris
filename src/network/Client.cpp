//
// Created by Ashley on 17.04.2024.
//

#include "../../include/Client.h"

void Client::connect(unsigned short port, IpAddress serverAddress) {

    socket.setBlocking(false);
    socket.connect(serverAddress, port);

    cout << "Connected to server" << endl;

}

bool ** Client::send(bool **data) {

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
void Client::transmit(char *message) {

    Packet sendPacket;
    for (int i = 0; i < sizeof(message); i++) {
        sendPacket << message[i];
    }

    Socket::Status sendStatus = socket.send(sendPacket);
    if (sendStatus == sf::Socket::Done) {
        cout << "Transmitted message: " << message << endl;
    } else {
        cerr << "Failed to send message" << endl;
    }


}
char * Client::receive() {

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