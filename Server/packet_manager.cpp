#include <iostream>
#include <sstream>
#include "packet_manager.h"

using namespace std ;

Packet_manager::Packet_manager(Server* srv)
{
	this->server = srv;
}


Packet_manager::~Packet_manager()
{

}


void Packet_manager::decode(char* buffer)
{
	//cout<<buffer<<endl ;
	stringstream ss ;
	string message ;
	int is_valid = 0 ;
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
		is_valid = server->register_user(username, password, email) ;
		if (is_valid == 0)
		{
			message = "It's OK." ;
			strncpy (buffer, message.c_str(), 512) ;
		}
		else
		{
			message = "It's not OK." ;
			strncpy (buffer, message.c_str(), 512) ;
		}
	}

	else if ( code == "010")
	{
		string  username , password ;
		ss >> username ;
		ss >> password ;
		//cout<<username<<"-"<<password<<"-"<<endl ;
		is_valid = server->login_user (username, password) ;
		if (is_valid == 0)
		{
			message = "It's OK." ;
			strncpy (buffer, message.c_str(), 512) ;
		}
		else
		{
			message = "It's not OK." ;
			strncpy (buffer, message.c_str(), 512) ;
		}
	}	


	//string temp(buffer);
	//cout << temp << endl;
}
