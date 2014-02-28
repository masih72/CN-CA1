#include <sstream>
#include <iostream>
#include <string>
#include <cstring>
#include "packet_manager.h"


Packet_manager::Packet_manager(Client* cli)
{
	this->client = cli;
}


Packet_manager::~Packet_manager()
{

}


void prepare_register_pack(char* buffer, stringstream& ss)
{
	buffer[0] = '0' ;
	buffer[1] = '0' ;
	buffer[2] = '0' ;
	buffer[3] = '1' ;
	buffer[4] = ' ' ;
	string username, password, email;
	ss >> username ;
	ss >> password ;
	ss >> email ;
	int index = 5 ;

	strncpy (&buffer[index], username.c_str(), PACKET_SIZE - index) ;
	index += username.length() + 1 ;
	buffer[index-1] = ' ' ;
	strncpy (&buffer[index], password.c_str(), PACKET_SIZE - index) ;
	index += password.length() + 1  ;
	buffer[index-1] = ' ' ;
	strncpy (&buffer[index], email.c_str(), PACKET_SIZE - index) ;
	//cout<<buffer<<endl ;
}

void prepare_login_pack(char* buffer, stringstream& ss)
{
	buffer[0] = '0' ;
	buffer[1] = '0' ;
	buffer[2] = '1' ;
	buffer[3] = '0' ;
	buffer[4] = ' ' ;
	string username, password ;
	ss >> username ;
	ss >> password ;
	int index = 5 ;

	strncpy (&buffer[index], username.c_str(), PACKET_SIZE - index) ;
	index += username.length() + 1 ;
	buffer[index-1] = ' ' ;
	strncpy (&buffer[index], password.c_str(), PACKET_SIZE - index) ;
	//cout<<buffer<<endl ;
}


void prepare_ChangeStatus_pack(char* buffer, stringstream& ss) 
{
	buffer[0] = '0' ;
	buffer[1] = '0' ;
	buffer[2] = '1' ;
	buffer[3] = '1' ;
	buffer[4] = ' ' ;
	string status ;
	ss >> status ;
	int index = 5 ;
	strncpy (&buffer[index], status.c_str(), PACKET_SIZE - index) ;
	//cout<<buffer<<endl ;
}

void prepare_invite_pack(char* buffer, stringstream& ss) 
{
	buffer[0] = '0' ;
	buffer[1] = '1' ;
	buffer[2] = '0' ;
	buffer[3] = '0' ;
	buffer[4] = ' ' ;
	string username ;
	ss >> username ;
	int index = 5 ;
	strncpy (&buffer[index], username.c_str(), PACKET_SIZE - index) ;
	//cout<<buffer<<endl ;
}

void prepare_accept_pack(char* buffer, stringstream& ss)
{
	buffer[0] = '0';
	buffer[1] = '1';
	buffer[2] = '0';
	buffer[3] = '1';
	buffer[4] = ' ';
	string username;
	ss >> username;
	int index = 5;
	strncpy(&buffer[index], username.c_str(), PACKET_SIZE - index);
	//cout << buffer << endl;
}

void prepare_deny_pack(char* buffer, stringstream& ss)
{
	buffer[0] = '0';
	buffer[1] = '1';
	buffer[2] = '1';
	buffer[3] = '0';
	buffer[4] = ' ';
	string username;
	ss >> username;
	int index = 5;
	strncpy(&buffer[index], username.c_str(), PACKET_SIZE - index);
	//cout << buffer << endl;
}

void prepare_select_pack(char* buffer, stringstream& ss)
{
	buffer[0] = '0';
	buffer[1] = '1';
	buffer[2] = '1';
	buffer[3] = '1';
	buffer[4] = ' ';
	string username;
	ss >> username;
	int index = 5;
	strncpy(&buffer[index], username.c_str(), PACKET_SIZE - index);
	//cout << buffer << endl;
}

void prepare_send_pack(char* buffer, stringstream& ss)
{
	buffer[0] = '1';
	buffer[1] = '0';
	buffer[2] = '0';
	buffer[3] = '0';
	buffer[4] = ' ';
	string message;
	getline(ss, message);
	int index = 5;
	strncpy(&buffer[index], message.c_str(), PACKET_SIZE - index);
	//cout << buffer << endl;
}

void prepare_exit_pack(char* buffer, stringstream& ss)
{
	buffer[0] = '1';
	buffer[1] = '0';
	buffer[2] = '0';
	buffer[3] = '1';
	buffer[4] = ' ';
	//cout << buffer << endl;
}

void prepare_who_pack(char* buffer, stringstream& ss)
{
	buffer[0] = '1';
	buffer[1] = '0';
	buffer[2] = '1';
	buffer[3] = '0';
	buffer[4] = ' ';
	string username_email;
	ss >> username_email;
	int index = 5;
	strncpy(&buffer[index], username_email.c_str(), PACKET_SIZE - index);
	//cout << buffer << endl;
}

void Packet_manager::encode(char* buffer, string command)
{
	//cout<<sizeof(buffer)<<endl ;
	stringstream ss ;
	ss << command ;
	string token  ;
	ss >> token ;
	if (token == "Register")
	{
		prepare_register_pack(buffer, ss) ;

	}
	else if ( token == "Login")
	{
		prepare_login_pack(buffer, ss) ;
	}
	else if ( token == "ChangeStatus")
	{
		prepare_ChangeStatus_pack(buffer, ss) ;
	}
	else if ( token == "Invite")
	{
		prepare_invite_pack(buffer, ss) ;
	}
	else if (token == "Accept")
	{
		prepare_accept_pack(buffer, ss);
	}
	else if (token == "Deny")
	{
		prepare_deny_pack(buffer, ss);
	}
	else if (token == "Select")
	{
		prepare_select_pack(buffer, ss);
	}
	else if (token == "Send")
	{
		prepare_send_pack(buffer, ss);
	}
	else if (token == "Exit")
	{
		prepare_exit_pack(buffer, ss);
	}
	else if (token == "Who")
	{
		prepare_who_pack(buffer, ss);
	}
	
}
