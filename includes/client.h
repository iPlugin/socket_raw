#ifndef CLIENT_H
#define CLIENT_H

#include "../includes/utils.h"


class Client{
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

// ----------------------------------------------------

    // package senderPacket;
    // sockaddr_in sendAddr;




 
    // startClient
    bool parseArgs(char *argv[]);
    bool createSocket();


    // // technical function
    // void printAndLogs(string &msg_type, string &message, bool status);
    // void waitSecond();

public:

    Client(const string &logFilePath): logger(logFilePath){}
    ~Client(){}

    bool startClient(char *argv[]);
// ----------------------------------------------------
    bool sendPacket();
    bool recv_packet();

};

#endif // CLIENT_H           ▐███████▌
//                           ▐       ▌
//                     ▄▀▀▀█ ▐ ▀▀▄▀▀ ▌ █▀▀▀▄
//                     ▌▌▌▌▐ ▄▌ ▄▄▄ ▐▄ ▌▐▐▐▐