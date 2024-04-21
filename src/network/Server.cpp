//
// Created by Ashley on 17.04.2024.
//

#include "../../include/Server.h"

void Server::connect(unsigned short port) {

    listener.setBlocking(false);
    listener.listen(port);

    socket.setBlocking(false);

    listener.accept(socket);

    selector.add(listener);
    selector.add(socket);


}

void Server::waitForClients() {

    if (selector.wait(milliseconds(100))) {
        if (selector.isReady(listener)) {

            if (listener.accept(client) == sf::Socket::Done) {
                selector.add(client);
            }
        }
    }

}

void Server::transmit(char *message) {

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
char * Server::receive() {

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