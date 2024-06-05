#include "../includes/server.h"

/*
----------------
---- Part 1 ----
----------------
*/

bool Server::startServer(int argc, char* argv[]){
    string msg_type_clt = "[ SERVER ]\t";
    string msg_type_arg = "[ PARAMS ]\t";
    string msg_type_sok = "[ SOCKET ]\t";
    string msg_type_con = "[ CONNECT ]\t";
    string msg_type_lis = "[ LISTEN ]\t";
    string msg_type_acp = "[ ACCEPT ]\t";

    string start_server = "Starting ...\n";
    cerr << BOLDGREEN << msg_type_clt << RESET << start_server;
    logger.log(msg_type_clt + start_server, Logger::INFO);

    if (parseArgs(argc, argv)){
        string msg_done = "Server received arguments\n";
        cerr << BOLDGREEN << msg_type_arg << RESET << msg_done;
        logger.log(msg_type_arg + msg_done, Logger::INFO);
    }
    else{
        string msg_error = "Server received no arguments\n\n";
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

    if (serverListen()){
        string msg_done = "Server started listening\n";
        cerr << BOLDGREEN << msg_type_lis << RESET << msg_done;
        logger.log(msg_type_lis + msg_done, Logger::INFO);
    }
    else{
        string msg_error = "Server did not start listening\n\n";
        cerr << BOLDRED << msg_type_lis << RESET << msg_error;
        logger.log(msg_type_lis + msg_error, Logger::INFO);
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

bool Server::connectServer(){
    int connect = createAddr(serverFD, server_ip, server_port, address);
    if (connect == 0)
        return true;
    return false;
}

bool Server::serverListen(){
    int result = listen(serverFD, 10);
    if (result == 0)
        return true;
    return false;
}