////
//// Created by Ashley on 18.02.2024.
////
//
//#ifndef TETRIS_NETWORKHANDLER_H
//#define TETRIS_NETWORKHANDLER_H
//
//#include <iostream>
//#include <iomanip>
//#include <optional>
//
//#include "SFML/Network.hpp"
//
//using namespace sf;
//using namespace std;
//
//class NetworkHandler {
//public:
//
//    void start();
//    void connectServer(unsigned short port);
//    void connectClient(unsigned short port, IpAddress serverAddress);
//    bool waitForClients();
//    bool ** send(bool **data);
//    void transmit(char *message);
//    char * receive();
//
//private:
//
//    TcpListener listener;
//    SocketSelector selector;
//    TcpSocket socket, client;
//    unsigned short port;
//
//};
//
//#endif //TETRIS_NETWORKHANDLER_H
