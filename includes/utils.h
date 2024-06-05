#ifndef UTILS_H
#define UTILS_H

#include <netinet/in.h> // + inside <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <string>
#include <charconv> // for from_chars


#include "../includes/colors.h"
#include "../includes/logger.h"
// #include "../includes/packages.h"

using namespace std;


int getSocket();
int createAddr(int socketFD, const string &ip, int port, sockaddr_in &address);
bool check_args(int argc, char* argv[], char *envp[], int count);

#endif  // UTILS_H