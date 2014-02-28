#include <iostream>
#include <cstring>
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
			strncpy (buffer, message.c_str(), PACKET_SIZE) ;
		}
		else
		{
			message = "Duplicate Username or Email." ;
			strncpy (buffer, message.c_str(), PACKET_SIZE) ;
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
			strncpy (buffer, message.c_str(), PACKET_SIZE) ;
		}
		else
		{
			message = "Wrong Username or Password." ;
			strncpy (buffer, message.c_str(), PACKET_SIZE) ;
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
			strncpy (buffer, message.c_str(), PACKET_SIZE) ;
		}
		else
		{
			message = "Wrong Status." ;
			strncpy (buffer, message.c_str(), PACKET_SIZE) ;
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
			strncpy (buffer, message.c_str(), PACKET_SIZE) ;
		}
		else if (is_valid == 1)
		{
			message = "Not Connected." ;
			strncpy (buffer, message.c_str(), PACKET_SIZE) ;
		}
		else if (is_valid == 2)
		{
			message = username+" Is Your Friend Already." ;
			strncpy (buffer, message.c_str(), PACKET_SIZE) ;
		}
		else if (is_valid == 3)
		{
			message = "Wrong Status.";
			strncpy (buffer, message.c_str(), PACKET_SIZE);
		}
		
	}	

	else if (code == "0101")
	{
		string username;
		ss >> username;
		is_valid = server->accept(username, cli_sock);
		if (is_valid == 0)
		{
			message = "It's OK." ;
			strncpy (buffer, message.c_str(), PACKET_SIZE) ;
		}
		else if (is_valid == 1)
		{
			message = "Not Connected." ;
			strncpy (buffer, message.c_str(), PACKET_SIZE) ;
		}
		else if (is_valid == 2)
		{
			message = "Wrong Status.";
			strncpy (buffer, message.c_str(), PACKET_SIZE);
		}
	}

	else if (code == "0110")
	{
		string username;
		ss >> username;
		is_valid = server->deny(username, cli_sock);
		if (is_valid == 0)
		{
			message = "It's OK." ;
			strncpy (buffer, message.c_str(), PACKET_SIZE) ;
		}
		else if (is_valid == 1)
		{
			message = "Not Connected." ;
			strncpy (buffer, message.c_str(), PACKET_SIZE) ;
		}
		else if (is_valid == 2)
		{
			message = "Wrong Status.";
			strncpy (buffer, message.c_str(), PACKET_SIZE);
		}
	}

	else if (code == "0111")
	{
		string username;
		ss >> username;
		is_valid = server->select(username, cli_sock);
		if (is_valid == 0)
		{
			message = "It's OK." ;
			strncpy (buffer, message.c_str(), PACKET_SIZE) ;
		}
		else if (is_valid == 1)
		{
			message = "Not Connected." ;
			strncpy (buffer, message.c_str(), PACKET_SIZE) ;
		}
		else if (is_valid == 2)
		{
			message = "Wrong Status.";
			strncpy (buffer, message.c_str(), PACKET_SIZE);
		}
		else if (is_valid == 3)
		{
			message = "Not Your Friend.";
			strncpy (buffer, message.c_str(), PACKET_SIZE);
		}
		else if (is_valid == 4)
		{
			message = "Friend Not Available.";
			strncpy(buffer, message.c_str(), PACKET_SIZE);
		}
	}

	else if (code == "1000")
	{
		string msg;
		getline(ss, msg);
		is_valid = server->send_msg(msg, cli_sock);
		if (is_valid == 0)
		{
			message = "It's OK.";
			strncpy(buffer, message.c_str(), PACKET_SIZE);
		}
		else if (is_valid == 1)
		{
			message = "Not Sent.";
			strncpy(buffer, message.c_str(), PACKET_SIZE);
		}
	}

	else if (code == "1001")
	{
		server->exit_client(cli_sock);
	}

	else if (code == "1010")
	{
		string username_email;
		ss >> username_email;
		is_valid = server->who(buffer,username_email, cli_sock);
		if (is_valid == 0)
		{

			message = "It's OK.";

		}
		else if (is_valid == 1)
		{
			message = "Not Found.";
			strncpy(buffer, message.c_str(), PACKET_SIZE);
		}
	}
	else
	{
			message = "Command Not Found.";
			strncpy(buffer, message.c_str(), PACKET_SIZE);
	}


}
