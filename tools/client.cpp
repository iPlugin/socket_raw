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
----------------    ▄▀    ▄▌─▄─▄─▐▄    ▀▄   Devil will break
---- Part 2 ----    █▄▄█  ▀▌─▀─▀─▐▀  █▄▄█       his head
----------------     ▐▌    ▀▀███▀▀    ▐▌
                    ████ ▄█████████▄ ████
*/

// void Client::msg_send(const string &message) {
//     // Підготовка IP і TCP заголовків
//     IPHeader ip_header{};
//     TCPHeader tcp_header{};

//     // Налаштування IP заголовку
//     ip_header.iph.version = 4;
//     ip_header.iph.ihl = 5;
//     ip_header.iph.tos = 0;
//     ip_header.iph.tot_len = htons(sizeof(IPHeader) + sizeof(TCPHeader) + message.size());
//     ip_header.iph.id = htons(54321);
//     ip_header.iph.frag_off = 0;
//     ip_header.iph.ttl = 255;
//     ip_header.iph.protocol = IPPROTO_TCP;
//     ip_header.iph.saddr = inet_addr("127.0.0.1"); // Встановлюєте адресу відправника (може бути змінена)
//     ip_header.iph.daddr = inet_addr(server_ip.c_str());

//     // Налаштування TCP заголовку
//     tcp_header.tcph.source = htons(server_port);
//     tcp_header.tcph.dest = htons(server_port);
//     tcp_header.tcph.seq = 0;
//     tcp_header.tcph.ack_seq = 0;
//     tcp_header.tcph.doff = 5;
//     tcp_header.tcph.fin = 0;
//     tcp_header.tcph.syn = 1; // Пізда якась звязана з підключенням
//     tcp_header.tcph.rst = 0;
//     tcp_header.tcph.psh = 0;
//     tcp_header.tcph.ack = 0;
//     tcp_header.tcph.urg = 0;
//     tcp_header.tcph.window = htons(5840); /* maximum allowed window size */
//     tcp_header.tcph.check = 0; // Потрібно обчислити пізніше
//     tcp_header.tcph.urg_ptr = 0;

//     // Підготовка повідомлення
//     SearchFile search_file{};
//     search_file.ip_header = ip_header;
//     search_file.tcp_header = tcp_header;
//     strncpy(search_file.filename, message.c_str(), sizeof(search_file.filename) - 1);
    
//     // Відправка повідомлення через сокет
//     size_t packet_size = sizeof(search_file);
//     ssize_t sent_bytes = send(clientFD, &search_file, packet_size, 0);

//     // Перевірка на успішну відправку
//     if (sent_bytes == -1) {
//         cerr << "Error sending message: " << strerror(errno) << endl;
//         logger.log("[ERROR]\tError sending message\n", Logger::ERROR);
//     } else {
//         cerr << "Message sent successfully\n";
//         logger.log("[INFO]\tMessage sent successfully\n", Logger::INFO);
//     }
// }





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