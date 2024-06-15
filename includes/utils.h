#ifndef UTILS_H
#define UTILS_H

#include <sys/socket.h>
#include <netinet/ip.h> // for struct iphdr
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <string>
#include <charconv> // for from_chars
#include <unistd.h> // for close()
#include <ctime>

#include "../includes/colors.h"
#include "../includes/logger.h"
#include "../package/package.h"
#include "../linux/settingsOS.h"
    // #include <sys/socket.h>
    // #include <netinet/in.h>

using namespace std;

// part 1
bool check_args(int argc, char *argv[], char *envp[], int count);
void printAndLogs(Logger &logger, string &msg_type, string &message, bool status);
void sleepTime(int sec);
int getSocket();

// part 2
// ----------------------------------------------------
unsigned short ip_checksum(void *vdata, int length);
unsigned short tcp_checksum(package *p);

void printData(Logger &logger, string &msg_type, string &packet);
void printPacket(const package &packet);


#endif  // UTILS_H