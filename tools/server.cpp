#include "../includes/server.h"

/*                         ▄   ▄
----------------       ▄█▄ █▀█▀█ ▄█▄
---- Part 1 ----      ▀▀████▄█▄████▀▀
----------------           ▀█▀█▀
*/

bool Server::startServer(char* argv[]){
    string msg_type_clt = "[ SERVER ]\t";
    string msg_type_arg = "[ PARAMS ]\t";
    string msg_type_sok = "[ SOCKET ]\t";
    string msg_type_bnd = "[ BIND ]\t";

    string start_server = "Starting ...\n";
    printAndLogs(logger, msg_type_clt, start_server, true);

    if (parseArgs(argv)){
        string message = "Server received arguments\n";
        printAndLogs(logger, msg_type_arg, message, true);
    }
    else{
        string message = "Server received no arguments\n\n";
        printAndLogs(logger, msg_type_arg, message, false);
        return false;
    }

    if (createSocket()){
        string message = "Socket was created\n";
        printAndLogs(logger, msg_type_sok, message, true);
    }
    else{
        string message = "Socket was not created\n\n";
        printAndLogs(logger, msg_type_sok, message, false);
        return false;
    }

    // if (serverBind()){
    //     string message = "Connection was successfully\n";
    //     printAndLogs(msg_type_bnd, message, true);
    // }
    // else{
    //     string message = "Connect was not created\n\n";
    //     printAndLogs(msg_type_bnd, message, false);
    //     return false;
    // }
    return true;
}

bool Server::parseArgs(char* argv[]){
    string temp_server_port = argv[1];
    string temp_proxy_port = argv[2];

    // server_ip = "";
    auto [ptr1, ec1] = std::from_chars(temp_server_port.data(), temp_server_port.data() + temp_server_port.size(), serverFD);
    if (ec1 != std::errc()) {
        std::cerr << "Помилка перетворення client_port: " << temp_server_port << std::endl;
        return false;
    }

    auto [ptr2, ec2] = std::from_chars(temp_proxy_port.data(), temp_proxy_port.data() + temp_proxy_port.size(), proxy_port);
    if (ec2 != std::errc()) {
        std::cerr << "Помилка перетворення proxy_port: " << temp_proxy_port << std::endl;
        return false;
    }

    return true;
}

bool Server::createSocket(){
    serverFD = getSocket();
    return serverFD;
}

// bool Server::serverBind(){
//     int result = createAddr(serverFD, server_ip, server_port, address);
//     if (result == 0)
//         return true;
//     close(serverFD);
//     return false;
// }

/*                         ▄█▄▄▄█▄
----------------    ▄▀    ▄▌─▄─▄─▐▄    ▀▄   Devil will break
---- Part 2 ----    █▄▄█  ▀▌─▀─▀─▐▀  █▄▄█       his head
----------------     ▐▌    ▀▀███▀▀    ▐▌
                    ████ ▄█████████▄ ████
*/

bool Server::send_packet(const string &message) {
    // Підготовка IP і TCP заголовків
    package packet; // IP + TCP + DATA
    
    packet.data = message;

    packet.iph.ihl = 5; 
    packet.iph.version = 4; 
    packet.iph.tos = 0; 
    packet.iph.tot_len = htons(sizeof(struct iphdr) + sizeof(struct tcphdr) + packet.data.size()); 
    packet.iph.id = htons(rand() % 65535); 
    packet.iph.frag_off = 0; 
    packet.iph.ttl = 64;
    packet.iph.protocol = IPPROTO_TCP; 
    packet.iph.check = 0; // ---------------------------------------------+
    packet.iph.saddr = inet_addr("127.0.0.1");                         // |
    packet.iph.daddr = inet_addr("127.0.0.1");                         // |
                                                                       // |
    packet.tcph.th_sport = htons(server_port);                         // |
    packet.tcph.th_dport = htons(proxy_port);                          // |
    packet.tcph.seq = 0;                                               // |
    packet.tcph.ack = 0;                                               // |
    packet.tcph.th_off = 5;                                            // |
    packet.tcph.res1 = 0;                                              // |
    packet.tcph.th_flags = TH_SYN;                                     // |
    packet.tcph.th_win = htons(5840);                                  // |
    packet.tcph.check = 0; // ----------------------------+               |
    packet.tcph.urg_ptr = 0; // if th_flags = TH_URG   // |               |
                                                       // |               |
    packet.tcph.check = tcp_checksum(&packet); // <-------+               |
    packet.iph.check = ip_checksum(&packet.iph, sizeof(packet.iph)); // <-+

    // Print the packet before sending
    std::cout << "\nSEND" << std::endl;
    printPacket(packet);

    // Destination address setup
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = packet.tcph.th_dport;
    address.sin_addr.s_addr = packet.iph.daddr;


    // Set option to include IP headers
    int one = 1;
    const int *val = &one;
    if (setsockopt(serverFD, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) < 0) {
        std::cerr << "Error setting IP_HDRINCL" << std::endl;
        close(serverFD);
        return 1;
    }

    // Send the packet
    char buffer[sizeof(package)];
    serialize_package(packet, buffer, sizeof(buffer));
    if (sendto(serverFD, buffer, ntohs(packet.iph.tot_len), 0, (sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Sendto failed" << std::endl;
    } else {
        std::cout << "Packet sent successfully" << std::endl;
    }

    return true;
}

bool Server::recv_packet() {
    while (true) {
        char buffer[4096]; // Буфер для "сырих" даних
        socklen_t addr_len = sizeof(sockaddr_in);
        sockaddr_in client_addr;

        // Приймаємо дані
        ssize_t packet_size = recvfrom(serverFD, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &addr_len);
        if (packet_size < 0) {
            std::cerr << "Recvfrom error" << std::endl;
            continue;
        }

        if (static_cast<size_t>(packet_size) < sizeof(iphdr) + sizeof(tcphdr)) {
            std::cerr << "Incomplete packet received" << std::endl;
            continue;
        }

        // Розпаковуємо дані у структуру package за допомогою функції deserialize_package
        package packet;
        deserialize_package(buffer, packet_size, packet);

        if (packet.iph.daddr == inet_addr("127.0.0.1") && packet.tcph.th_dport == htons(server_port) && packet.data != "") {
            // Виводимо прийнятий пакет
            std::cout << "\nRECV" << std::endl;
            printPacket(packet);
        }
    }
}











// 01:06 ━━━━⬤─────── 04:05
// ▁▂▃▄▅▆▇█ 𝙇𝙤𝙖𝙙𝙞𝙣𝙜…

/*
----------------------------
---- technical function ----
----------------------------
*/

// void Server::printAndLogs(string &msg_type, string &message, bool status){
//     if (status){
//         cerr << BOLDGREEN << msg_type << RESET << message;
//         logger.log(msg_type + message, Logger::INFO);
//     }
//     else{
//         cerr << BOLDRED << msg_type << RESET << message;
//         logger.log(msg_type + message, Logger::INFO);
//     }
// }