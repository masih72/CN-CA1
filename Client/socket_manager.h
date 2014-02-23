#ifndef SOCKET_MANAGER_H
#define SOCKET_MANAGER_H

class Client;

#include "client.h"

class Socket_manager
{
public:
	Socket_manager(Client* cli);
	virtual ~Socket_manager();

	void send(char* buffer);

private:
	int server_fd;
	Client* client;
};

#endif
