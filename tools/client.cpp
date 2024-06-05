#include "../includes/client.h"

/*                         ▄   ▄
----------------       ▄█▄ █▀█▀█ ▄█▄
---- Part 1 ----      ▀▀████▄█▄████▀▀
----------------           ▀█▀█▀
*/

bool Client::startClient(int argc, char* argv[]){
    string msg_type_clt = "[ CLIENT ]\t";
    string msg_type_arg = "[ PARAMS ]\t";
    string msg_type_sok = "[ SOCKET ]\t";
    string msg_type_con = "[ CONNECT ]\t";

    string start_client = "Starting ...\n";
    printAndLogs(msg_type_clt, start_client, true);

    if (parseArgs(argc, argv)){
        string message = "Client received arguments\n";
        printAndLogs(msg_type_arg, message, true);
    }
    else{
        string message = "Client received no arguments\n\n";
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

    if (connectServer()){
        string message = "Connection was successfully\n";
        printAndLogs(msg_type_con, message, true);
    }
    else{
        string message = "Connect was not created\n\n";
        printAndLogs(msg_type_con, message, false);
        return false;
    }
    return true;
}

bool Client::parseArgs(int argc, char* argv[]){
    string temp = argv[2];

    server_ip = argv[1];
    auto [ptr, ec] = std::from_chars(temp.data(), temp.data() + temp.size(), server_port);
    return ec == std::errc();
}

bool Client::createSocket(){
    clientFD = getSocket();
    return clientFD;
}

bool Client::connectServer(){
    int result = createAddr(clientFD, server_ip, server_port, address);
    if (result == 0)
        return true;
    close(clientFD);
    return false;
}

/*                         ▄█▄▄▄█▄
----------------    ▄▀    ▄▌─▄─▄─▐▄    ▀▄
---- Part 2 ----    █▄▄█  ▀▌─▀─▀─▐▀  █▄▄█
----------------     ▐▌    ▀▀███▀▀    ▐▌
                    ████ ▄█████████▄ ████
*/






/*
----------------------------
---- technical function ----
----------------------------
*/

void Client::printAndLogs(string &msg_type, string &message, bool status){
    if (status){
        cerr << BOLDGREEN << msg_type << RESET << message;
        logger.log(msg_type + message, Logger::INFO);
    }
    else{
        cerr << BOLDRED << msg_type << RESET << message;
        logger.log(msg_type + message, Logger::INFO);
    }
}