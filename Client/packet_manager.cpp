#include "packet_manager.h"


Packet_manager::Packet_manager(Client* cli)
{
	this->client = cli;
}


Packet_manager::~Packet_manager()
{

}


void Packet_manager::encode(char* buffer, string command)
{
	//TODO make the packet with header code and all the stuff here
}
