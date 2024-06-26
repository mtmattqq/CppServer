#ifndef TCP_LISTENER_HPP
#define TCP_LISTENER_HPP

#include <cstdlib>
#include <string>
#include <cstdint>
#include <netinet/in.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h>
#include "TcpStream.hpp"

class TcpListener {
private:
    const static int AUTO = 0;
    int socket_fd;
    sockaddr_in address;
    sockaddr_in client_address;
    socklen_t client_len;
    bool listen();
public:
    TcpListener(const std::string &ip_addr, const uint16_t &port);
    ~TcpListener();
    bool bind();
    TcpStream accept();
    sockaddr_in get_client_address();
};

#endif