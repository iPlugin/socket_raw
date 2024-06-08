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
    bool serverBind();
    
    void printAndLogs(string &msg_type, string &message, bool status);

public:

    Server(const string &logFilePath): logger(logFilePath){}
    ~Server(){}

    bool startServer(int argc, char *argv[]);
    void msg_recv();

};

#endif // SERVER_H           ▐███████▌
//                           ▐░░░░░░░▌
//                     ▄▀▀▀█ ▐░▀▀▄▀▀░▌ █▀▀▀▄
//                     ▌▌▌▌▐ ▄▌░▄▄▄░▐▄ ▌▐▐▐▐