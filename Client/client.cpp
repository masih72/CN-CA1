#include <iostream>
#include <cstring>
#include "client.h"

using namespace std;

Client::Client(char*& ip_addr, int port_num)
{
	this->ip_addr = ip_addr;
	this->port_num = port_num;
	this->packet_manager = new Packet_manager(this);
	this->socket_manager = new Socket_manager(this);
}


Client::~Client()
{
	delete this->packet_manager;
	delete this->socket_manager;
}


void Client::run()
{
	cout << "Welcome!" << endl << "Please enter your command:" << endl;
	while(1)
	{
		cout << ">>> ";

		string command;
		getline(cin, command) ;

		char buffer[PACKET_SIZE];
		bzero(buffer, sizeof(buffer));
		this->packet_manager->encode(buffer, command);

		this->socket_manager->send(buffer);
	}
}
