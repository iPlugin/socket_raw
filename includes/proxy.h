#ifndef PROXY_H
#define PROXY_H

#include "../includes/utils.h"


class Proxy{
private:
    // constructor
    Logger logger;

    // startProxy -> parseArgs
    string proxy_ip;
    int proxy_port;
    int server_port;
    int client_port;

    // startClient -> createSocket
    int proxyFD;

    // sendPacket
    struct sockaddr_in sender_addr;
    // recvPacket
    struct sockaddr_in recver_addr;

    // startProxy
    bool parseArgs(char *argv[]);
    bool createSocket();
    bool createIp();


    bool send_packet(int sender, int receiver, std::string message);
    void print_packet(const package &packet);

public:
    Proxy(const string &logFilePath): logger(logFilePath){}
    ~Proxy(){}

    bool startProxy(char *argv[]);
    bool recv_packet();

};

#endif // PROXY_H            ▐███████▌
//                           ▐░░░░░░░▌
//                     ▄▀▀▀█ ▐░▀▀▄▀▀░▌ █▀▀▀▄
//                     ▌▌▌▌▐ ▄▌░▄▄▄░▐▄ ▌▐▐▐▐