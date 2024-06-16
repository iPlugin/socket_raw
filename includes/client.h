#ifndef CLIENT_H
#define CLIENT_H

#include "../includes/utils.h"


class Client {
private:
    // constructor
    Logger logger;

    // startClient -> parseArgs
    string client_ip;
    int client_port;
    int proxy_port;
    string filename;

    // startClient -> createSocket
    int clientFD;

    // sendPacket
    struct sockaddr_in sender_addr;
    // recvPacket
    struct sockaddr_in recver_addr;
 
    // startClient
    bool parseArgs(char *argv[]);
    bool createSocket();
    bool createIp();

public:

    Client(const string &logFilePath): logger(logFilePath){}
    ~Client(){}

    bool startClient(char *argv[]);
    bool sendPacket();
    bool recvPacket();

};

#endif // CLIENT_H           ▐███████▌
//                           ▐       ▌
//                     ▄▀▀▀█ ▐ ▀▀▄▀▀ ▌ █▀▀▀▄
//                     ▌▌▌▌▐ ▄▌ ▄▄▄ ▐▄ ▌▐▐▐▐