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

bool Server::check_user_pass (string name, string pass, int cli_sock)
{
	//for (int i = 0 ; i < users.size() ; i++ )
	//{
		if (find_fd(cli_sock)->get_username() == name )
		{
			if (find_fd(cli_sock)->get_password() == pass)
			{
				return true ;
			}
		}
	//}
				
	return false ;	
}

User* Server::find_username (string name)
{
	for (int i = 0 ; i < users.size() ; i++ )
		if (this->users[i]->get_username() == name )
			return users[i] ;
	return 0 ;	

}

User* Server::find_fd (int sockfd)
{
	for (int i = 0 ; i < users.size() ; i++ )
		if (this->users[i]->get_client_fd() == sockfd )
			return users[i] ;
	return 0 ;
}

int Server::login_user (string username, string password, int cli_sock)
{
	if ( !check_user_pass(username, password, cli_sock) )
	{
		return 1 ;
	}
	else
	{
		find_username(username)->is_login = true ;
		return 0 ;
	}

}

int Server::register_user (string username, string password, string email, int cli_sock) 
{
	if (is_registered(username))
	{
		return 1 ;
	}	
	else
	{
		User* user = new User(username, password,email,cli_sock) ;
		cout<<user->get_client_fd()<<endl  ;
		this->users.push_back(user) ;
		//test() ;
		return 0 ;
	}
}

int Server::change_status (string status, int cli_sock) 
{

	if (status != "available" && status != "offline" && status != "busy")
	{
		return 1 ;
	}	
	else if (status == "available")
	{
		find_fd(cli_sock)->status = status ;
		return 0 ;
	}
	else if (status == "busy")
	{
		find_fd(cli_sock)->status = status ;
		return 0 ;
	}
	else
	{
		find_fd(cli_sock)->status = status ;
		find_fd(cli_sock)->is_login = false ;
		return 0 ;
	}
}


bool Server::is_friend (string name, int cli_sock)
{
	for (int i = 0 ; i < find_fd(cli_sock)->friends.size() ; i++)
		if (find_fd(cli_sock)->friends[i] == name)
			return true ;
	return false ;	
}


int Server::invitation (string username, int cli_sock)
{
	if ( (find_fd(cli_sock)->status == "offline") )
	{
		return 1 ;
	}
	else if (is_friend(username, cli_sock))
	{
		return 2 ;
	}
	else
	{
		//cout<<"girandeh : "<<find_username(username)->invitations<<endl ;
		//cout<<"ferestandeh : "<<find_fd(cli_sock)->username<<endl ;
		find_username(username)->invitations.push_back(find_fd(cli_sock)->username) ;
		//cout<<find_username(username)->invitations[0]->username<<endl ;
		//cout<<find_fd(cli_sock)->invitations[0]->username<<endl ;
		test() ;
		return 0 ;
	}
}


void Server::test()
{

	/*for (int i = 0 ; i < users.size() ; i++)
	{
		cout<<users[i]->username<<", " ;
	}*/
	for (int i = 0 ; i < users.size() ; i++)
	{
		cout<<users[i]->username<<"'s invitations is from : " ;
		for (int j = 0 ; j < users[i]->invitations.size(); j++)
			cout<<users[i]->invitations[j]<<" , " ;
		cout<<endl ;
	}
}










