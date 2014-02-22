#include <iostream>
#include <unistd.h>
#include "server.h"

using namespace std;

Server::Server(int port_num)
{
	this->port_num = port_num;
	this->socket_manager = new Socket_manager(this);
}

Server::~Server()
{
	delete this->socket_manager;
}

void Server::run()
{
	while(1)
	{
		cout << "server running..." << endl;
		usleep(3000000);
	}
}
