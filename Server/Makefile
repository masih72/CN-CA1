all: server

server: main.cpp server.o packet_manager.o socket_manager.o
	g++ -std=c++0x main.cpp server.o packet_manager.o socket_manager.o -lpthread -o server

server.o: server.cpp server.h
	g++ -std=c++0x -c server.cpp
	
packet_manager.o: packet_manager.cpp packet_manager.h
	g++ -std=c++0x -c packet_manager.cpp
	
socket_manager.o: socket_manager.cpp socket_manager.h
	g++ -std=c++0x -c socket_manager.cpp