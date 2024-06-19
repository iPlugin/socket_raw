#ifndef PACKAGE_H
#define PACKAGE_H

#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

// packet = IP + TCP + DATA
struct package{
    iphdr iph;           // IP заголовок
    tcphdr tcph;         // TCP заголовок
    std::string data;    // Дані для передачі
}; // SSO - small string optimization

struct sockaddr_in;


// Функція для серіалізації структури package в буфер
// std::optional<std::vector<char>>
void serialize_package(const package& pkt, char* buffer, size_t buffer_size) { // Should be part of package struct
    // Перевірка розміру буфера
    if (buffer_size < sizeof(iphdr) + sizeof(tcphdr) + pkt.data.size()) {
        std::cerr << "Buffer is too small for serialization" << std::endl;
        return; // User won't know that buffer is too small, return false at least
    }

    // Копіювання IP заголовка в буфер
    memcpy(buffer, &pkt.iph, sizeof(iphdr));
    buffer += sizeof(iphdr);

    // Копіювання TCP заголовка в буфер
    memcpy(buffer, &pkt.tcph, sizeof(tcphdr));
    buffer += sizeof(tcphdr);

    // Копіювання даних в буфер
    memcpy(buffer, pkt.data.c_str(), pkt.data.size());
}

// Функція для десеріалізації структури package з буфера
void deserialize_package(const char* buffer, size_t buffer_size, package& pkt) {
    // Перевірка розміру буфера
    if (buffer_size < sizeof(iphdr) + sizeof(tcphdr)) {
        std::cerr << "Buffer is too small for deserialization" << std::endl;
    }

    // Копіювання IP заголовка з буфера в структуру package
    memcpy(&pkt.iph, buffer, sizeof(iphdr));
    buffer += sizeof(iphdr);

    // Копіювання TCP заголовка з буфера в структуру package
    memcpy(&pkt.tcph, buffer, sizeof(tcphdr));
    buffer += sizeof(tcphdr);

    // Десеріалізація даних з буфера в структуру package
    pkt.data.assign(buffer, buffer_size - sizeof(iphdr) - sizeof(tcphdr));
}


#endif // PACKAGE_H