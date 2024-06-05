#include "../includes/server.h"

/*                         ▄   ▄
----------------       ▄█▄ █▀█▀█ ▄█▄
---- Part 1 ----      ▀▀████▄█▄████▀▀
----------------           ▀█▀█▀
*/

bool Server::startServer(int argc, char* argv[]){
    string msg_type_clt = "[ SERVER ]\t";
    string msg_type_arg = "[ PARAMS ]\t";
    string msg_type_sok = "[ SOCKET ]\t";
    string msg_type_bnd = "[ BIND ]\t";

    string start_server = "Starting ...\n";
    printAndLogs(msg_type_clt, start_server, true);

    if (parseArgs(argc, argv)){
        string message = "Server received arguments\n";
        printAndLogs(msg_type_arg, message, true);
    }
    else{
        string message = "Server received no arguments\n\n";
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

    if (serverBind()){
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

bool Server::parseArgs(int argc, char* argv[]){
    string temp = argv[1];

    server_ip = "";
    auto [ptr, ec] = std::from_chars(temp.data(), temp.data() + temp.size(), server_port);
    return ec == std::errc();
}

bool Server::createSocket(){
    serverFD = getSocket();
    return serverFD;
}

bool Server::serverBind(){
    int result = createAddr(serverFD, server_ip, server_port, address);
    if (result == 0)
        return true;
    close(serverFD);
    return false;
}

/*                         ▄█▄▄▄█▄
----------------    ▄▀    ▄▌─▄─▄─▐▄    ▀▄
---- Part 2 ----    █▄▄█  ▀▌─▀─▀─▐▀  █▄▄█
----------------     ▐▌    ▀▀███▀▀    ▐▌
                    ████ ▄█████████▄ ████
*/

void Server::msg_recv(){
    
}






// 01:06 ━━━━⬤─────── 04:05
// ▁▂▃▄▅▆▇█ 𝙇𝙤𝙖𝙙𝙞𝙣𝙜…

/*
----------------------------
---- technical function ----
----------------------------
*/

void Server::printAndLogs(string &msg_type, string &message, bool status){
    if (status){
        cerr << BOLDGREEN << msg_type << RESET << message;
        logger.log(msg_type + message, Logger::INFO);
    }
    else{
        cerr << BOLDRED << msg_type << RESET << message;
        logger.log(msg_type + message, Logger::INFO);
    }
}