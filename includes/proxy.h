#ifndef PROXY_H
#define PROXY_H

#include "../includes/utils.h"


class Proxy{
private:
    int proxyFD;
    string proxy_ip;
    int client_port;
    int proxy_port;
    int server_port;
    Logger logger;
    struct sockaddr_in address;

    bool parseArgs(int argc, char *argv[]);
    bool createSocket();
    bool proxyBind();
    
    void printAndLogs(string &msg_type, string &message, bool status);

public:
    Proxy(const string &logFilePath): logger(logFilePath){}
    ~Proxy(){}

    bool startProxy(int argc, char *argv[]);

};

#endif // PROXY_H            ▐███████▌
//                           ▐░░░░░░░▌
//                     ▄▀▀▀█ ▐░▀▀▄▀▀░▌ █▀▀▀▄
//                     ▌▌▌▌▐ ▄▌░▄▄▄░▐▄ ▌▐▐▐▐