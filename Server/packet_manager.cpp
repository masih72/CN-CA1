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


void Packet_manager::decode(char* buffer, int cli_sock)
{
	//cout<<"client socket : "<<cli_sock<< endl ;
	stringstream ss ;
	string message ;
	int is_valid = 0 ;
	string code ;
	ss << buffer ;
	ss >> code ;
	if ( code == "0001")
	{
		string  username , password , email ;
		ss >> username ;
		ss >> password ;
		ss >> email ;
		//cout<<username<<"-"<<password<<"-"<<email<<endl ;
		is_valid = server->register_user(username, password, email, cli_sock) ;
		if (is_valid == 0)
		{
			message = "It's OK." ;
			strncpy (buffer, message.c_str(), 512) ;
		}
		else
		{
			message = "Duplicate Username or Email." ;
			strncpy (buffer, message.c_str(), 512) ;
		}
	}

	else if ( code == "0010")
	{
		string  username , password ;
		ss >> username ;
		ss >> password ;
		//cout<<username<<"-"<<password<<"-"<<endl ;
		is_valid = server->login_user (username, password, cli_sock) ;
		if (is_valid == 0)
		{
			message = "It's OK." ;
			strncpy (buffer, message.c_str(), 512) ;
		}
		else
		{
			message = "Wrong Username or Password." ;
			strncpy (buffer, message.c_str(), 512) ;
		}
	}

	else if ( code == "0011")
	{
		string status ;
		ss >> status ;
		//cout<<username<<"-"<<password<<"-"<<endl ;
		is_valid = server->change_status (status, cli_sock) ;
		if (is_valid == 0)
		{
			message = "It's OK." ;
			strncpy (buffer, message.c_str(), 512) ;
		}
		else
		{
			message = "Wrong Status." ;
			strncpy (buffer, message.c_str(), 512) ;
		}

	}	

	else if ( code == "0100")
	{
		string username ;
		ss >> username ;
		//cout<<username<<"-"<<password<<"-"<<endl ;
		is_valid = server->invitation (username, cli_sock) ;
		if (is_valid == 0)
		{
			message = "It's OK." ;
			strncpy (buffer, message.c_str(), 512) ;
		}
		else if (is_valid == 1)
		{
			message = "Not Connected." ;
			strncpy (buffer, message.c_str(), 512) ;
		}
		else if (is_valid == 2)
		{
			message = username+" Is Your Friend Already." ;
			strncpy (buffer, message.c_str(), 512) ;
		}
		
	}	


	//string temp(buffer);
	//cout << temp << endl;
}
