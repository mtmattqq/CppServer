#include "TcpListener.hpp"
#include "TcpStream.hpp"
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <vector>

void handle_connection(TcpStream &tcp_stream) {
    std::fstream in("index.html");
    std::string content, line;
    while(getline(in, line)) {
        content += line + "\n";
    }

    std::string http{
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: " + 
        std::to_string(content.size()) + 
        "\r\n\r\n" + 
        content
    };

    std::vector<uint8_t> request;
    tcp_stream.recv(request, 1024);
    for(int i{0}; i < request.size() && request[i] != 0; ++i) {
        std::cout << char(request[i]);
    }

    tcp_stream.send(http);
}

int main(int argc, char *args[]) {
    if(argc == 1) {
        std::cerr << "Too few argument: need port number" << "\n";
        return 0;
    }

    TcpListener tcp_listener("0.0.0.0", atoi(args[1]));
    while(true) {
        TcpStream tcp_stream{tcp_listener.accept()};
        if(tcp_stream.failed()) {
            break;
        }
        
        sockaddr_in client_address = tcp_listener.get_client_address();
        std::cout << "Client IP: " 
                  << std::string(inet_ntoa(client_address.sin_addr)) << ":"
                  << uint16_t(ntohs(client_address.sin_port)) << std::endl;
        handle_connection(tcp_stream);
    }
}