#include "client.h"

Client::Client(char*& ip_addr, int port_num)
{
	this->ip_addr = ip_addr;
	this->port_num = port_num;
	this->socket_manager = new Socket_manager(this);
}


Client::~Client()
{
	delete this->socket_manager;
}


void Client::run()
{

}
