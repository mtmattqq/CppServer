#include "TcpStream.hpp"
#include <cstddef>
#include <cstdint>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

TcpStream::TcpStream(const std::string &ip_addr, const uint16_t &port)
    : socket_fd(socket(AF_INET, SOCK_STREAM, AUTO)),
      address{
        .sin_family = AF_INET,
        .sin_port = htons(port),
      }
{
    inet_pton(AF_INET, ip_addr.c_str(), &address.sin_addr.s_addr);
}

TcpStream::TcpStream(const sockaddr_in &_address, const int &_socket_fd) 
    : address(_address), socket_fd(_socket_fd) {}

TcpStream::~TcpStream() {
    close(socket_fd);
}

bool TcpStream::connect() {
    int result = ::connect(socket_fd, (const sockaddr*) &address, sizeof(address));
    return result != -1;
}

int TcpStream::send(std::vector<uint8_t> &data) {
    const int DEFAULT{0};
    uint8_t buf[64];
    size_t cur{0};
    while(cur < data.size()) {
        size_t len{0};
        for(len = 0; len < 64 && cur + len < data.size(); ++len) {
            buf[len] = data[cur + len];
        }
        cur += len;
        ssize_t result{::send(
            socket_fd, (void*) buf, 
            data.size() * sizeof(uint8_t), DEFAULT)};
        if(result == -1) {
            return -1;
        }
    }
    return 0;
}

int TcpStream::send(std::string &data) {
    const int DEFAULT{0};
    uint8_t buf[1024];
    size_t cur{0};
    while(cur < data.size()) {
        size_t len{0};
        for(len = 0; len < 1024 && cur + len < data.size(); ++len) {
            buf[len] = data[cur + len];
        }
        cur += len;
        ssize_t result{::send(
            socket_fd, (void*) buf, 
            data.size() * sizeof(uint8_t), DEFAULT)};
        if(result == -1) {
            return -1;
        }
    }
    return 0;
}