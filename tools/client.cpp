#include "../includes/client.h"

/*                         ▄   ▄
----------------       ▄█▄ █▀█▀█ ▄█▄         I am            ----------------
---- Part 1 ----      ▀▀████▄█▄████▀▀       Batman           ---- Part 1 ----
----------------           ▀█▀█▀                             ----------------
*/

bool Client::startClient(char* argv[]){
    string msg_type_clt = "[ CLIENT ]\t";
    string msg_type_arg = "[ PARAMS ]\t";
    string msg_type_sok = "[ SOCKET ]\t";

    string start_client = "Starting ...\n";
    printAndLogs(logger, msg_type_clt, start_client, true);

    sleepTime(1);

    if (parseArgs(argv)){
        string message = "Client received arguments\n";
        printAndLogs(logger, msg_type_arg, message, true);
    }
    else{
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
    return true;
}

bool Client::parseArgs(char* argv[]){
    client_ip = "127.0.0.1"; // Client::client_ip

    string temp_port = argv[1]; // Client::client_port
    auto [ptr1, ec1] = std::from_chars(temp_port.data(),
        temp_port.data() + temp_port.size(), client_port);
    if (ec1 != std::errc()) {
        logger.log("Error convert client_port", Logger::ERROR);
        return false; 
    }

    temp_port = argv[2]; // Client::proxy_port
    auto [ptr2, ec2] = std::from_chars(temp_port.data(),
        temp_port.data() + temp_port.size(), proxy_port);
    if (ec2 != std::errc()) {
        logger.log("Error convert proxy_port", Logger::ERROR);
        return false;
    }

    filename = argv[3]; // Client::filename
    return true;
}

bool Client::createSocket(){
    clientFD = getSocket();
    return clientFD;
}

/*                         ▄█▄▄▄█▄
----------------    ▄▀    ▄▌─▄─▄─▐▄    ▀▄   Devil will break ----------------
---- Part 2 ----    █▄▄█  ▀▌─▀─▀─▐▀  █▄▄█       his head     ---- Part 2 ----
----------------     ▐▌    ▀▀███▀▀    ▐▌                     ----------------
                    ████ ▄█████████▄ ████
*/

bool Client::sendPacket() {
    package packet; // IP + TCP + DATA
    
    // Data
    packet.data = filename;

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
    packet.iph.saddr = inet_addr(client_ip.c_str());                   // |
    packet.iph.daddr = inet_addr(client_ip.c_str());                   // |
                                                                       // |
    packet.tcph.th_sport = htons(client_port);                         // |
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

// ----------------------------------------------------
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
    if (setsockopt(clientFD, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) < 0) {
        std::cerr << "Error setting IP_HDRINCL" << std::endl;
        close(clientFD);
        return 1;
    }

    // Send the packet
    char buffer[sizeof(package)];
    serialize_package(packet, buffer, sizeof(buffer));
    if (sendto(clientFD, buffer, ntohs(packet.iph.tot_len), 0, (sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Sendto failed" << std::endl;
    } else {
        std::cout << "Packet sent successfully" << std::endl;
    }

    return true;
}

bool Client::recv_packet() {
    while (true) {
        char buffer[4096]; // Буфер для "сырих" даних
        socklen_t addr_len = sizeof(sockaddr_in);
        sockaddr_in client_addr;

        // Приймаємо дані
        ssize_t packet_size = recvfrom(clientFD, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &addr_len);
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

        if (packet.iph.daddr == inet_addr("127.0.0.1") && packet.tcph.th_dport == htons(client_port) && packet.data != "") {
            // Виводимо прийнятий пакет
            std::cout << "\nRECV" << std::endl;
            printPacket(packet);
        }
    }
}




/*
----------------------------
---- technical function ----
----------------------------
*/