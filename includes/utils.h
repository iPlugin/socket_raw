#ifndef UTILS_H
#define UTILS_H


// #include "../includes/logger.h"
// #include "../includes/console_colors.h"
// #include "../includes/packages.h"

#include <netinet/in.h> // + inside <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>

using namespace std;


int getSocket();
int createAddr(int socketFD, const string &ip, int port, sockaddr_in &address);


#endif  // UTILS_H