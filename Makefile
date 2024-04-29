CXX=g++
CXXFLAGS=-std=c++17 -static

main: main.o TcpListener.o TcpStream.o
	g++ main.o TcpListener.o TcpStream.o -o main
client: client.o TcpStream.o
	g++ client.o TcpStream.o -o client