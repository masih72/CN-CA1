#include <iostream>
#include <unistd.h>
#include <vector>
#include "server.h"

using namespace std;

vector<User*> Server::users ;

Server::Server(int port_num)
{
	this->port_num = port_num;
	this->packet_manager = new Packet_manager(this);
	this->socket_manager = new Socket_manager(this);
	//this->users = new vector<User*>() ;
}

Server::~Server()
{
	delete this->packet_manager;
	delete this->socket_manager;
}

void Server::run()
{
	cout << "server running..." << endl;
	while(1)
	{
		//usleep(300000000);
	}
}

bool Server::is_registered(string name)
{
	for (int i = 0 ; i < users.size() ; i++ )
		if (this->users[i]->get_username() == name )
			return true ;
	return false ;
}

bool is_login(string name)
{
	return false ;
}

bool Server::check_user_pass (string name, string pass)
{
	for (int i = 0 ; i < users.size() ; i++ )
	{
		if (this->users[i]->get_username() == name )
		{
			if (this->users[i]->get_password() == pass)
			{
				return true ;
			}
		}
	}
				
	return false ;	
}

User* Server::find_username (string name)
{
	for (int i = 0 ; i < users.size() ; i++ )
		if (this->users[i]->get_username() == name )
			return users[i] ;
	return 0 ;	

}



int Server::login_user (string username, string password)
{
	if ( !check_user_pass(username, password) )
	{
		return 1 ;
	}
	else
	{
		find_username(username)->is_login = true ;
		return 0 ;
	}

}

int Server::register_user (string username, string password, string email) 
{
	if (is_registered(username))
	{
		return 1 ;
	}	
	else
	{
		User* user = new User(username, password,email) ;
		cout<<user->get_username()<<endl  ;
		this->users.push_back(user) ;
		return 0 ;
	}
}

















