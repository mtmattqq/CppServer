#ifndef TCP_STREAM_HPP
#define TCP_STREAM_HPP

#include <cstdlib>
#include <string>
#include <cstdint>
#include <netinet/in.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h>
#include <vector>

class TcpStream {
private:
    const static int AUTO = 0;
    int socket_fd;
    sockaddr_in address;
public:
    TcpStream(const std::string &ip_addr, const uint16_t &port);
    TcpStream(const sockaddr_in &address, const int &sockfd);
    ~TcpStream();
    bool connect();
    bool failed() { return socket_fd == -1;}
    int send(std::vector<uint8_t> &data);
    int send(std::string &data);
};

#endif