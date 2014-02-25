#include <iostream>
#include <sstream>
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
	cout<<buffer<<endl ;
	stringstream ss ;
	string code ;
	ss << buffer ;
	ss >> code ;
	if ( code == "001")
	{
		string  username , password , email ;
		ss >> username ;
		ss >> password ;
		ss >> email ;
		//cout<<username<<"-"<<password<<"-"<<email<<endl ;
		server->register_users (username, password, email) ;
	}	

	//string temp(buffer);
	//cout << temp << endl;
}
