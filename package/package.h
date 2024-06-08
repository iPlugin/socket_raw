#ifndef PACKAGE_H
#define PACKAGE_H

#include <variant>
#include <netinet/ip.h>
#include <netinet/tcp.h>

#pragma pack(push, 1)

// Headers
struct IPHeader{
    struct iphdr iph;
};

struct TCPHeader{
    struct tcphdr tcph;
};

// Type messages
struct ServerIntro{
    IPHeader ip_header;
    TCPHeader tcp_header;
    char intro[2048];
};

struct SearchFile{
    IPHeader ip_header;
    TCPHeader tcp_header;
    char filename[50];
};

struct PleaseWait{
    IPHeader ip_header;
    TCPHeader tcp_header;
    char plswait[30];
};

struct ResultPath{
    IPHeader ip_header;
    TCPHeader tcp_header;
    char result[50];
};

using Package = std::variant<ServerIntro, SearchFile, PleaseWait, ResultPath>;

#pragma pack(pop)

#endif // PACKAGE_H