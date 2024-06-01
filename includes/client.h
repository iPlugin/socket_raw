#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <cstring>
#include <charconv> // for from_chars
// #include <string>

#include "../includes/utils.h"
#include "../includes/logger.h"
#include "../includes/colors.h"
// #include "../package/package.h"

#define debug

class Client{
private:
    int clientFD;
    Logger logger;
    struct sockaddr_in address;

    string server_ip;
    int server_port;

    bool parseArgs(int argc, char* argv[]);
    bool createSocket();
    bool connectServer();

public:

    Client(const string& logFilePath): logger(logFilePath){}
    ~Client(){}

    bool startClient(int argc, char* argv[]);

};

#endif