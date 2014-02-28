#ifndef SOCKET_MANAGER_H
#define SOCKET_MANAGER_H

class Client;

#include <thread>
#include "client.h"

using namespace std;

class Socket_manager
{
public:
	Socket_manager(Client* cli);
	virtual ~Socket_manager();

	void send(char* buffer);
	static void receive(Socket_manager* socket_manager);

private:
	int server_fd;
	Client* client;
	thread* receiver;
};

#endif
