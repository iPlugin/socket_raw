#include "../includes/proxy.h"

/*                         ▄   ▄
----------------       ▄█▄ █▀█▀█ ▄█▄
---- Part 1 ----      ▀▀████▄█▄████▀▀
----------------           ▀█▀█▀
*/

bool Proxy::startProxy(int argc, char* argv[]){
    string msg_type_clt = "[ PROXY ]\t";
    string msg_type_arg = "[ PARAMS ]\t";
    string msg_type_sok = "[ SOCKET ]\t";
    string msg_type_bnd = "[ BIND ]\t";

    string start_proxy = "Starting ...\n";
    printAndLogs(msg_type_clt, start_proxy, true);

    if (parseArgs(argc, argv)){
        string message = "Proxy received arguments\n";
        printAndLogs(msg_type_arg, message, true);
    }
    else{
        string message = "Proxy received no arguments\n\n";
        printAndLogs(msg_type_arg, message, false);
        return false;
    }

    if (createSocket()){
        string message = "Socket was created\n";
        printAndLogs(msg_type_sok, message, true);
    }
    else{
        string message = "Socket was not created\n\n";
        printAndLogs(msg_type_sok, message, false);
        return false;
    }

    if (proxyBind()){
        string message = "Connection was successfully\n";
        printAndLogs(msg_type_bnd, message, true);
    }
    else{
        string message = "Connect was not created\n\n";
        printAndLogs(msg_type_bnd, message, false);
        return false;
    }
    return true;
}

bool Proxy::parseArgs(int argc, char* argv[]){
    string temp = argv[1];

    proxy_ip = temp; // ПЕРЕВІРКА ДАНИХ
    auto [ptr, ec] = std::from_chars(temp.data(), temp.data() + temp.size(), proxy_port);
    return ec == std::errc();
}

bool Proxy::createSocket(){
    return getSocket();
}

bool Proxy::proxyBind(){
    int result = createAddr(proxyFD, proxy_ip, proxy_port, address);
    if (result == 0)
        return true;
    close(proxyFD);
    return false;
}

/*                         ▄█▄▄▄█▄
----------------    ▄▀    ▄▌─▄─▄─▐▄    ▀▄   Devil will break
---- Part 2 ----    █▄▄█  ▀▌─▀─▀─▐▀  █▄▄█       his head
----------------     ▐▌    ▀▀███▀▀    ▐▌
                    ████ ▄█████████▄ ████
*/












// 01:06 ━━━━⬤─────── 04:05
// ▁▂▃▄▅▆▇█ 𝙇𝙤𝙖𝙙𝙞𝙣𝙜…

/*
----------------------------
---- technical function ----
----------------------------
*/

void Proxy::printAndLogs(string &msg_type, string &message, bool status){
    if (status){
        cerr << BOLDGREEN << msg_type << RESET << message;
        logger.log(msg_type + message, Logger::INFO);
    }
    else{
        cerr << BOLDRED << msg_type << RESET << message;
        logger.log(msg_type + message, Logger::INFO);
    }
}