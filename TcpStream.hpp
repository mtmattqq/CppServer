#include <cstdlib>
#include <string>
#include <cstdint>
#include <netinet/in.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h>

class TcpStream {
private:
    const static int AUTO = 0;
    int socket_fd;
    sockaddr_in address;
public:
    TcpStream(const std::string &ip_addr, const uint16_t &port);
    ~TcpStream();
    bool connect();
};