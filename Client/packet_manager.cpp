#include <sstream>
#include <iostream>
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
	buffer[2] = '1' ;
	buffer[3] = ' ' ;
	string username, password, email;
	ss >> username ;
	ss >> password ;
	ss >> email ;
	int index = 4 ;

	strncpy (&buffer[index], username.c_str(), sizeof(buffer)) ;
	index += username.length() + 1 ;
	buffer[index-1] = ' ' ;
	strncpy (&buffer[index], password.c_str(), sizeof(buffer)) ;
	index += password.length() + 1  ;
	buffer[index-1] = ' ' ;
	strncpy (&buffer[index], email.c_str(), sizeof(buffer)) ;
	cout<<buffer<<endl ;
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

}
else if ( token == "ChangeStatus")
{

}

	
}
