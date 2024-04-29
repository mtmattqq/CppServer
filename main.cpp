#include "TcpListener.hpp"
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <string>

int main(int argc, char *args[]) {
    if(argc == 1) {
        std::cerr << "Too few argument: need port number" << "\n";
        return 0;
    }

    TcpListener tcp_listener("0.0.0.0", atoi(args[1]));
    while(tcp_listener.accept() != -1) {
        sockaddr_in client_address = tcp_listener.get_client_address();
        std::cout << "Client IP: " 
                  << std::string(inet_ntoa(client_address.sin_addr)) << ":"
                  << uint16_t(ntohs(client_address.sin_port)) << std::endl;
    }
}