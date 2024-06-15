#ifndef SERVER_H
#define SERVER_H

#include "../includes/utils.h"


class Server{
private:
    // constructor
    Logger logger;

    // startServer -> parseArgs
    string server_ip;
    int server_port;
    int proxy_port;

    // startServer -> createSocket
    int serverFD;

    // sendPacket
    struct sockaddr_in sender_addr;
    // recvPacket
    struct sockaddr_in recver_addr;
    string filename;

    // startServer
    bool parseArgs(char *argv[]);
    bool createSocket();
    bool createIp();

public:

    Server(const string &logFilePath): logger(logFilePath){}
    ~Server(){}

    bool startServer(char *argv[]);
// -------------------------------------------------
    bool sendPacket(const string &message);
    bool recvPacket();

};

#endif // SERVER_H           ▐███████▌
//                           ▐       ▌
//                     ▄▀▀▀█ ▐ ▀▀▄▀▀ ▌ █▀▀▀▄
//                     ▌▌▌▌▐ ▄▌ ▄▄▄ ▐▄ ▌▐▐▐▐