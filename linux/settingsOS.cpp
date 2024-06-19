#include "settingsOS.h"

// class SocketRaw
// Name is not clear
bool settingIp(int &socketFD) { // reference is extra here, pass by copy
    int one = 1;
    const int *val = &one; // not needed, but OK
    if (setsockopt(socketFD, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) >= 0) {
        return true;
    }
    return false;   
}