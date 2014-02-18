#include <iostream>
#include "server.h"

using namespace std;

Server::Server(int port_num)
{
	this->port_num = port_num;
	this->socket_manager = new Socket_manager();
}

Server::~Server()
{
	delete this->socket_manager;
}

void Server::run()
{
	cout << "running" << endl;	
}