#ifndef SERVER_H
#define SERVER_H

class Packet_manager;
class Socket_manager;

#include "packet_manager.h"
#include "socket_manager.h"

class Server
{
public:
	Server(int port_num);
	virtual ~Server();

	void run();

	int get_port_num() { return port_num; }
	Packet_manager* get_packet_manager() { return packet_manager; }

private:
	int port_num;
	Packet_manager* packet_manager;
	Socket_manager* socket_manager;
};


#endif
