#include "../includes/proxy.h"

/*                         ▄   ▄
----------------       ▄█▄ █▀█▀█ ▄█▄         I am            ----------------
---- Part 1 ----      ▀▀████▄█▄████▀▀       Batman           ---- Part 1 ----
----------------           ▀█▀█▀                             ----------------
*/

bool Proxy::startProxy(char* argv[]) {
    string msg_type_clt = "[ PROXY ]\t";
    string msg_type_arg = "[ PARAMS ]\t";
    string msg_type_sok = "[ SOCKET ]\t";
    string msg_type_hrl = "[ HDRINCL ]\t";

    string start_proxy = "Starting ...\n";
    printAndLogs(logger, msg_type_clt, start_proxy, true);

    sleepTime(1);

    if (parseArgs(argv)){
        string message = "Client received arguments\n";
        printAndLogs(logger, msg_type_arg, message, true);
    }
    else {
        string message = "Client received no arguments\n\n";
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
        close(proxyFD);
        return false;
    }

    sleepTime(1);
    return true;
}

bool Proxy::parseArgs(char* argv[]) {
    proxy_ip = "127.0.0.1"; // Proxy::client_ip

    string temp_port = argv[2]; // Proxy::proxy_port
    auto [ptr1, ec1] = std::from_chars(temp_port.data(),
        temp_port.data() + temp_port.size(), proxy_port);
    if (ec1 != std::errc()) {
        logger.log("Error convert proxy_port\n", Logger::WARNING);
        return false; 
    }

    temp_port = argv[3]; // Proxy::server_port
    auto [ptr2, ec2] = std::from_chars(temp_port.data(),
        temp_port.data() + temp_port.size(), server_port);
    if (ec2 != std::errc()) {
        logger.log("Error convert server_port\n", Logger::WARNING);
        return false;
    }

    temp_port = argv[4]; // Proxy::client_port
    auto [ptr3, ec3] = std::from_chars(temp_port.data(),
        temp_port.data() + temp_port.size(), client_port);
    if (ec3 != std::errc()) {
        logger.log("Error convert client_port\n", Logger::WARNING);
        return false;
    }
    return true;
}

bool Proxy::createSocket() {
    proxyFD = getSocket();
    return proxyFD;
}

bool Proxy::createIp() {
    if (settingIp(proxyFD))
        return true;
    return false;
}

/*                         ▄█▄▄▄█▄
----------------    ▄▀    ▄▌─▄─▄─▐▄    ▀▄   Devil will break ----------------
---- Part 2 ----    █▄▄█  ▀▌─▀─▀─▐▀  █▄▄█       his head     ---- Part 2 ----
----------------     ▐▌    ▀▀███▀▀    ▐▌                     ----------------
                    ████ ▄█████████▄ ████
*/

bool Proxy::send_packet(int sender, int receiver, std::string message) {
    package packet; // IP + TCP + DATA
    
    packet.data = message;

    packet.iph.ihl = 5; 
    packet.iph.version = 4; 
    packet.iph.tos = 0; 
    packet.iph.tot_len = htons(sizeof(struct iphdr) + sizeof(struct tcphdr) + packet.data.size()); 
    packet.iph.id = htons(rand() % 65535);; 
    packet.iph.frag_off = 0; 
    packet.iph.ttl = 64;
    packet.iph.protocol = IPPROTO_TCP; 
    packet.iph.check = 0; // ---------------------------------------------+
    packet.iph.saddr = inet_addr(proxy_ip.c_str());                    // |
    packet.iph.daddr = inet_addr(proxy_ip.c_str());                    // |
                                                                       // |
    packet.tcph.th_sport = htons(sender);                              // |
    packet.tcph.th_dport = htons(receiver);                            // |
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
    print_packet(packet);

    // Destination address setup
    sender_addr.sin_family = AF_INET;
    sender_addr.sin_addr.s_addr = packet.iph.daddr;
    sender_addr.sin_port = packet.tcph.th_dport;

    // Send the packet
    char buffer[2048];
    serialize_package(packet, buffer, sizeof(buffer));
    if (sendto(proxyFD, buffer, ntohs(packet.iph.tot_len), 0, (sockaddr*)&sender_addr, sizeof(sender_addr)) < 0)
        std::cerr << "Sendto failed" << std::endl;
    else
        std::cout << "Packet sent successfully" << std::endl;

    return true;
}

bool Proxy::recv_packet() {
    while (true) {
        char buffer[2048];
        socklen_t recver_addr_len = sizeof(sockaddr_in);
        ssize_t packet_size = recvfrom(proxyFD, buffer, sizeof(buffer), 0, (struct sockaddr*)&recver_addr, &recver_addr_len);

        // Upload packet
        package packet;
        deserialize_package(buffer, packet_size, packet);

        if (packet.iph.daddr == inet_addr(proxy_ip.c_str()) && packet.tcph.th_dport == htons(proxy_port) && !packet.data.empty()) {
            std::cout << "\nRECV" << std::endl;
            print_packet(packet);

            if (packet.tcph.th_sport == htons(client_port)) {
                send_packet(proxy_port, server_port, packet.data);
            }
            else if (packet.tcph.th_sport == htons(server_port)) {
                send_packet(proxy_port, client_port, packet.data);
            }
        }
    }
    return true;
}

void Proxy::print_packet(const package &packet) {
    std::cout << "Sending packet:" << std::endl;
    std::cout << "Package ID: " << packet.iph.id << std::endl;
    std::cout << "Source IP: " << inet_ntoa(*(in_addr*)&packet.iph.saddr) << std::endl;
    std::cout << "Destination IP: " << inet_ntoa(*(in_addr*)&packet.iph.daddr) << std::endl;
    std::cout << "Source Port: " << ntohs(packet.tcph.th_sport) << std::endl;
    std::cout << "Destination Port: " << ntohs(packet.tcph.th_dport) << std::endl;
    std::cout << "Data: " << packet.data << std::endl;
}








// 01:06 ━━━━⬤─────── 04:05
// ▁▂▃▄▅▆▇█ 𝙇𝙤𝙖𝙙𝙞𝙣𝙜…

/*
----------------------------
---- technical function ----
----------------------------
*/
