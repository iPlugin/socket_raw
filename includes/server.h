#ifndef SERVER_H
#define SERVER_H

#include "../includes/utils.h"


class Server{
private:
    int serverFD;
    int clientFD;
    Logger logger;
    struct sockaddr_in address;

    string server_ip;
    int server_port;

    bool parseArgs(int argc, char *argv[]);
    bool createSocket();
    bool connectServer();
    bool serverListen();
    bool serverAccept();

public:

    Server(const string &logFilePath): logger(logFilePath){}
    ~Server(){}

    bool startServer(int argc, char *argv[]);
    // bool send_pkg(string &message);

};

#endif // SERVER_H