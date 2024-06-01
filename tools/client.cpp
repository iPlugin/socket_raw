#include "../includes/client.h"

bool Client::startClient(int argc, char* argv[]){
    string msg_type_clt = "[ CLIENT ]\t";
    string msg_type_arg = "[ PARAMS ]\t";
    string msg_type_sok = "[ SOCKET ]\t";
    string msg_type_con = "[ CONNECT ]\t";

    string start_client = "Starting ...\n";
    cerr << BOLDGREEN << msg_type_clt << RESET << start_client;
    logger.log(msg_type_clt + start_client, Logger::INFO);

    if (parseArgs(argc, argv)){
        string msg_done = "Client received arguments\n";
        cerr << BOLDGREEN << msg_type_arg << RESET << msg_done;
        logger.log(msg_type_arg + msg_done, Logger::INFO);
    }
    else{
        string msg_error = "Client received no arguments\n\n";
        cerr << BOLDRED << msg_type_arg << RESET << msg_error;
        logger.log(msg_type_arg + msg_error, Logger::ERROR);
        return false;
    }

    if (createSocket()){
        string msg_done = "Socket was created\n";
        cerr << BOLDGREEN << msg_type_sok << RESET << msg_done;
        logger.log(msg_type_sok + msg_done, Logger::INFO);
    }
    else{
        string msg_error = "Socket was not created\n\n";
        cerr << BOLDRED << msg_type_sok << RESET << msg_error;
        logger.log(msg_type_sok + msg_error, Logger::ERROR);
        return false;
    }

    if (connectServer()){
        string msg_done = "Connection was successfully\n";
        cerr << BOLDGREEN << msg_type_con << RESET << msg_done;
        logger.log(msg_type_con + msg_done, Logger::INFO);
    }
    else{
        string msg_error = "Connect was not created\n\n";
        cerr << BOLDRED << msg_type_con << RESET << msg_error;
        logger.log(msg_type_con + msg_error, Logger::INFO);
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
    int connect = createAddr(clientFD, server_ip, server_port, address);
    if (connect == 0)
        return true;
    return false;
}