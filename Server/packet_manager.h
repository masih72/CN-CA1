#ifndef PACKET_MANAGER_H
#define PACKET_MANAGER_H

class Server;

#include "server.h"

#define PACKET_SIZE 512

class Packet_manager
{
public:
	Packet_manager(Server* srv);
	virtual ~Packet_manager();

	void decode(char* buffer);

private:
	Server* server;
};

#endif
