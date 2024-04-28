#include "TcpStream.hpp"

TcpStream::TcpStream(const std::string &ip_addr, const uint16_t &port) {
    socket_fd = socket(AF_INET, SOCK_STREAM, AUTO);
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_pton(AF_INET, ip_addr.c_str(), &address.sin_addr.s_addr);
}

TcpStream::~TcpStream() {
    close(socket_fd);
}

bool TcpStream::connect() {
    int result = ::connect(socket_fd, (const sockaddr*) &address, sizeof(address));
    return result != -1;
}