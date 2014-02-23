#include <iostream>
#include "packet_manager.h"

Packet_manager::Packet_manager(Server* srv)
{
	this->server = srv;
}


Packet_manager::~Packet_manager()
{

}


void Packet_manager::decode(char* buffer)
{
	string temp(buffer);
	cout << temp << endl;
}
