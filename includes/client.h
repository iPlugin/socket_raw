#ifndef CLIENT_H
#define CLIENT_H

#include "../includes/utils.h"


class Client{
private:
    int clientFD;
    Logger logger;
    struct sockaddr_in address;

    string server_ip;
    int server_port;

    bool parseArgs(int argc, char *argv[]);
    bool createSocket();
    bool connectServer();

public:

    Client(const string &logFilePath): logger(logFilePath){}
    ~Client(){}

    bool startClient(int argc, char *argv[]);
    // bool send_pkg(string &message);

};

#endif // CLIENT_H