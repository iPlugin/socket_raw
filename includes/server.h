#ifndef SERVER_H
#define SERVER_H

#include "../includes/utils.h"


class Server{
private:
    int serverFD;
    Logger logger;
    struct sockaddr_in address;

    // string server_ip;
    // int server_port;

    // string client_ip;
    int server_port;
    int proxy_port;

    bool parseArgs(char *argv[]);
    bool createSocket();
    // bool serverBind();
    
    // void printAndLogs(string &msg_type, string &message, bool status);

public:

    Server(const string &logFilePath): logger(logFilePath){}
    ~Server(){}

    bool startServer(char *argv[]);
    bool send_packet(const string &message);
    bool recv_packet();

};

#endif // SERVER_H           ▐███████▌
//                           ▐       ▌
//                     ▄▀▀▀█ ▐ ▀▀▄▀▀ ▌ █▀▀▀▄
//                     ▌▌▌▌▐ ▄▌ ▄▄▄ ▐▄ ▌▐▐▐▐