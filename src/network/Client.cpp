//
// Created by Ashley on 17.04.2024.
//

#include "../../include/Client.h"

void Client::connect(unsigned short port, IpAddress serverAddress) {

    socket.setBlocking(false);
    socket.connect(serverAddress, port);

    cout << "Connected to server" << endl;

}

void Client::transmit(char *message) {

    Packet sendPacket;
    for (int i = 0; i < sizeof(message); i++) {
        sendPacket << message[i];
    }

    Socket::Status sendStatus = socket.send(sendPacket);
    if (sendStatus == sf::Socket::Done) {
        std::cout << "Game started status transmitted successfully\n";
    } else if (sendStatus == sf::Socket::Partial) {
        std::cerr << "Partial send occurred. Data might not have been fully transmitted\n";
    } else if (sendStatus == Socket::Error) {
        std::cerr << "Failed to transmit gameStarted packet. Error code: " << sendStatus << std::endl;
    }


}
char * Client::receive() {

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