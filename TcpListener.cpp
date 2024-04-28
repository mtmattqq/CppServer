#include "TcpListener.hpp"
#include <iostream>

bool TcpListener::listen() {
    int result = ::listen(socket_fd, 20);
    return result != -1;
}

TcpListener::TcpListener(const std::string &ip_addr, const uint16_t &port) {
    socket_fd = socket(AF_INET, SOCK_STREAM, AUTO);
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_pton(AF_INET, ip_addr.c_str(), &address.sin_addr.s_addr);
    if(bind()) {
        std::cout << "Bind to the port: " << port << "successfully!\n";
    } else {
        std::cout << "Binding to the port: " << port << "failed\n";
    }
    if(listen()) {
        std::cout << "Listenning to the port: " << port << "\n";
    } else {
        std::cout << "Listenning failed!" << "\n";
    }
}

TcpListener::~TcpListener() {
    close(socket_fd);
}