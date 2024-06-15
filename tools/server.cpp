#include "../includes/server.h"

/*                         ▄   ▄
----------------       ▄█▄ █▀█▀█ ▄█▄         I am            ----------------
---- Part 1 ----      ▀▀████▄█▄████▀▀       Batman           ---- Part 1 ----
----------------           ▀█▀█▀                             ----------------
*/

bool Server::startServer(char* argv[]) {
    string msg_type_clt = "[ SERVER ]\t";
    string msg_type_arg = "[ PARAMS ]\t";
    string msg_type_sok = "[ SOCKET ]\t";
    string msg_type_hrl = "[ HDRINCL ]\t";

    string start_server = "Starting ...\n";
    printAndLogs(logger, msg_type_clt, start_server, true);

    sleepTime(1);

    if (parseArgs(argv)) {
        string message = "Server received arguments\n";
        printAndLogs(logger, msg_type_arg, message, true);
    }
    else {
        string message = "Server received no arguments\n\n";
        printAndLogs(logger, msg_type_arg, message, false);
        return false;
    }

    sleepTime(1);

    if (createSocket()) {
        string message = "Socket was created\n";
        printAndLogs(logger, msg_type_sok, message, true);
    }
    else {
        string message = "Socket was not created\n\n";
        printAndLogs(logger, msg_type_sok, message, false);
        return false;
    }

    sleepTime(1);

    if (createIp()) {
        string message = "Setting IP_HDRINCL successfully\n";
        printAndLogs(logger, msg_type_hrl, message, true);
    }
    else {
        string message = "Error setting IP_HDRINCL\n\n";
        printAndLogs(logger, msg_type_hrl, message, false);
        close(serverFD);
        return false;
    }

    sleepTime(1);
    return true;
}

bool Server::parseArgs(char* argv[]) {
    server_ip = "127.0.0.1"; // Server::server_ip

    string temp_port = argv[1]; // Server::server_port
    auto [ptr1, ec1] = std::from_chars(temp_port.data(),
        temp_port.data() + temp_port.size(), server_port);
    if (ec1 != std::errc()) {
        logger.log("Error convert server_port", Logger::ERROR);
        return false; 
    }

    temp_port = argv[2]; // Server::proxy_port
    auto [ptr2, ec2] = std::from_chars(temp_port.data(),
        temp_port.data() + temp_port.size(), proxy_port);
    if (ec2 != std::errc()) {
        logger.log("Error convert proxy_port", Logger::ERROR);
        return false;
    }

    return true;
}

bool Server::createSocket() {
    serverFD = getSocket();
    return serverFD;
}

bool Server::createIp() {
    if (settingIp(serverFD)) {
        return true;
    }
    return false;
}

/*                         ▄█▄▄▄█▄
----------------    ▄▀    ▄▌─▄─▄─▐▄    ▀▄   Devil will break ----------------
---- Part 2 ----    █▄▄█  ▀▌─▀─▀─▐▀  █▄▄█       his head     ---- Part 2 ----
----------------     ▐▌    ▀▀███▀▀    ▐▌                     ----------------
|                   ████ ▄█████████▄ ████
*/

bool Server::sendPacket(const string &answer) {
    string msg_type_snd = "[ SEND ]\t";

    package packet; // IP + TCP + DATA
    
    // Data
    packet.data = answer;

    // IP і TCP заголовки
    packet.iph.ihl = 5; 
    packet.iph.version = 4; 
    packet.iph.tos = 0; 
    packet.iph.tot_len = htons(sizeof(struct iphdr) + sizeof(struct tcphdr) + packet.data.size()); 
    packet.iph.id = htons(rand() % 65535); 
    packet.iph.frag_off = 0; 
    packet.iph.ttl = 64;
    packet.iph.protocol = IPPROTO_TCP; 
    packet.iph.check = 0; // ---------------------------------------------+
    packet.iph.saddr = inet_addr(server_ip.c_str());                   // |
    packet.iph.daddr = inet_addr(server_ip.c_str());                   // |
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


    // Server::sender_addr
    sender_addr.sin_family = AF_INET;
    sender_addr.sin_addr.s_addr = packet.iph.daddr;
    sender_addr.sin_port = packet.tcph.th_dport;

    // Send the packet
    char buffer[4096];
    serialize_package(packet, buffer, sizeof(buffer));
    if (sendto(serverFD, buffer, ntohs(packet.iph.tot_len), 0, (sockaddr*)&sender_addr, sizeof(sender_addr)) > 0) {
        string message = "Packet: " + packet.data + "\n";
        packet.data = answer + "\n";
        printAndLogs(logger, msg_type_snd, message, true);
    }
    else {
        string message = "Send failed\n\n";
        packet.data = answer + "\n";
        printAndLogs(logger, msg_type_snd, message, false);
    }

    return true;
}

bool Server::recvPacket() {
    string msg_type_rcv = "[ RECV ]\t";

    while (true) {
        char buffer[4096];
        socklen_t recver_addr_len = sizeof(sockaddr_in);
        ssize_t packet_size = recvfrom(serverFD, buffer, sizeof(buffer), 0, (struct sockaddr*)&recver_addr, &recver_addr_len);
        
        // Upload packet
        package packet;
        deserialize_package(buffer, packet_size, packet);

        if (packet.iph.daddr == inet_addr("127.0.0.1") && packet.tcph.th_dport == htons(server_port) && packet.data != "") {
            string message = "Packet: " + packet.data + "\n";
            printAndLogs(logger, msg_type_rcv, message, true);
            filename = packet.data;
            break;
        }
    }

    return true;
}

/*                 ▄▀▀▀▀▀▄      ▄▄▄▄▄
----------------  ▐ ▄   ▄ ▌   ▄█▄█▄█▄█▄   File search        ----------------
---- Part 3 ----  ▐ ▀▀ ▀▀ ▌      ▒░▒         by file name    ---- Part 2 ----
----------------   ▀▄ ═ ▄▀       ▒░▒                         ----------------
|                  ▐ ▀▄▀ ▌       ▒░▒     ▁▂▃▄▅▆▇█ 𝙇𝙤𝙖𝙙𝙞𝙣𝙜…
*/

