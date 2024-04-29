#include "TcpStream.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    if(argc == 1) {
        std::cerr << "Too few argument: need port number" << "\n";
        return 0;
    }
    TcpStream tcp_stream("127.0.0.0", atoi(argv[1]));
    if(tcp_stream.connect()) {
        std::cout << "Connection established" << "\n";
    } else {
        std::cerr << "Connection failed" << "\n";
    }
}