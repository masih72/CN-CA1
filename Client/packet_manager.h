#ifndef PACKET_MANAGER_H
#define PACKET_MANAGER_H

class Client;

#include <string>
#include "client.h"

using namespace std;

#define PACKET_SIZE 512

class Packet_manager
{
public:
	Packet_manager(Client* cli);
	virtual ~Packet_manager();

	void encode(char* buffer, string command);

private:
	Client* client;
};

#endif
