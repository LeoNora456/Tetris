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

            TcpSocket *client = new TcpSocket();
            clients.push_back(client);
            if (listener.accept(*client) == sf::Socket::Done) {
                selector.add(*client);
            }
        }
    }

}

void Server::transmit(char *message) {

    Packet packet;
    packet << message;
    socket.send(packet);

}
char * Server::receive() {

    Packet packet;
    socket.receive(packet);

    char *message;
    packet >> message;

    return message;

}