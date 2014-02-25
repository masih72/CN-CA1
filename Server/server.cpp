#include <iostream>
#include <unistd.h>
#include "server.h"

using namespace std;

Server::Server(int port_num)
{
	this->port_num = port_num;
	this->packet_manager = new Packet_manager(this);
	this->socket_manager = new Socket_manager(this);
}

Server::~Server()
{
	delete this->packet_manager;
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

void Server::register_users (string username, string password, string email) 
{

}
