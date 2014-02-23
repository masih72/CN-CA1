#ifndef CLIENT_H
#define CLIENT_H

class Packet_manager;
class Socket_manager;

#include "packet_manager.h"
#include "socket_manager.h"

class Client
{
public:
	Client(char*& ip_addr, int port_num);
	virtual ~Client();

	void run();

	char* get_ip_addr() { return this->ip_addr; }
	int get_port_num() { return this->port_num; }

private:
	char* ip_addr;
	int port_num;
	Packet_manager* packet_manager;
	Socket_manager* socket_manager;
};

#endif
