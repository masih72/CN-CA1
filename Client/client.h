#ifndef CLIENT_H
#define CLIENT_H

class Socket_manager;

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
	Socket_manager* socket_manager;
};

#endif
