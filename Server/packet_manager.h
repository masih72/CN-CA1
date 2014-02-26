#ifndef PACKET_MANAGER_H
#define PACKET_MANAGER_H

class Server;

#include "server.h"

using namespace std ;

#define PACKET_SIZE 512

class Packet_manager
{
public:
	Packet_manager(Server* srv);
	virtual ~Packet_manager();

	void decode(char* buffer, int cli_sock);

private:
	Server* server;
};

#endif
