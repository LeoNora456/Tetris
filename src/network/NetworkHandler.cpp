//
// Created by Ashley on 18.02.2024.
//


#include "../../include/NetworkHandler.h"

void NetworkHandler::connectServer(unsigned short port) {

    listener.listen(port);
    bool connected = false;
    while (!listener.listen(port)) {
        if (listener.accept(socket) == Socket::Done) {
            connected = true;
        }
    }



    // Listen to the given port for incoming connections
    if (listener.listen(port) != sf::Socket::Status::Done)
        return;
    cout << "Server is listening to port " << port << ", waiting for connections... " << endl;

    // Wait for a connection
    TcpSocket socket;
    if (listener.accept(socket) != sf::Socket::Status::Done)
        return;
    std::cout << "Client connected: " << socket.getRemoteAddress().toInteger() << std::endl;


}
void NetworkHandler::connectClient(unsigned short port, IpAddress serverAddress) {

    socket.connect(serverAddress, port);

// Ask for the server address
    std::optional<sf::IpAddress> server;
    do
    {
        std::cout << "Type the address or name of the server to connect to: ";
        std::cin >> reinterpret_cast<bool &>(server);
    } while (!server.has_value());

    // Create a socket for communicating with the server
    sf::TcpSocket socket;

    // Connect to the server
    if (socket.connect(server.value(), port) != sf::Socket::Status::Done)
        return;
    std::cout << "Connected to server " << server.value() << std::endl;

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