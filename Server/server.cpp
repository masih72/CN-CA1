#include <iostream>
#include <cstring>
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
	for (int i=0 ; i<users.size() ; ++i)
		delete users[i];
}

void Server::run()
{
	cout << "server running..." << endl;
	while(1)
	{
		usleep(300000000);
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
	for (int i=0 ; i<users.size() ; ++i)
	{
		if (users[i]->get_username() == name && users[i]->get_password() == pass)
			return true;
	}
				
	return false;
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
	if ( !check_user_pass(username, password) )
	{
		return 1 ;
	}
	else
	{
		find_username(username)->is_login = true ;
		find_username(username)->client_fd = cli_sock;
		find_username(username)->status = "available";
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
		//cout<<user->get_client_fd()<<endl  ;
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
		//find_fd(cli_sock)->is_login = false ;
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
	if ( find_fd(cli_sock)->is_login == false)
	{
		return 1;
	}
	else if ( (find_username(username)->status == "offline") )
	{
		return 3 ;
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
		//test() ;
		char buffer[PACKET_SIZE];
		string message = "invitation from: " + find_fd(cli_sock)->username;
		strncpy(buffer, message.c_str(), PACKET_SIZE);

		this->socket_manager->send(buffer, find_username(username)->client_fd);

		return 0 ;
	}
}


int Server::accept(string username, int cli_sock)
{
	if ( find_fd(cli_sock)->is_login == false)
	{
		return 1;
	}
	else if ( (find_fd(cli_sock)->status == "offline") )
	{
		return 2;
	}
	else
	{
		find_fd(cli_sock)->friends.push_back(username);
		find_username(username)->friends.push_back(find_fd(cli_sock)->get_username());

		return 0;
	}
}


int Server::deny(string username, int cli_sock)
{
	if ( find_fd(cli_sock)->is_login == false)
	{
		return 1;
	}
	else if ( (find_fd(cli_sock)->status == "offline") )
	{
		return 2;
	}
	else
	{
		return 0;
	}
}


int Server::select(string username, int cli_sock)
{
	if ( find_fd(cli_sock)->is_login == false)
	{
		return 1;
	}
	else if ( (find_fd(cli_sock)->status == "offline") )
	{
		return 2;
	}
	else if (!find_fd(cli_sock)->has_friend(username))
	{
		return 3;
	}
	else if (find_username(username)->status != "available")
	{
		return 4;
	}
	else
	{
		find_fd(cli_sock)->set_selected_friend(username);
		return 0;
	}
}


int Server::send_msg(string msg, int cli_sock)
{

	char buffer[PACKET_SIZE];
	string message = find_fd(cli_sock)->get_username() + ":" + msg;
	strncpy(buffer, message.c_str(), PACKET_SIZE);

	if (find_fd(cli_sock)->get_selected_friend() == "")
		return 1;

	string des_status = find_username(find_fd(cli_sock)->get_selected_friend())->get_status();
	if (des_status == "busy" || des_status == "offline")
		return 1;
	if (find_username(find_fd(cli_sock)->get_selected_friend())->get_username() != find_fd(cli_sock)->get_username() )
		this->socket_manager->send(buffer, find_username(find_fd(cli_sock)->get_selected_friend())->get_client_fd());

	return 0 ;
}


int Server::exit_client(int cli_sock)
{
	User* client = find_fd(cli_sock);
	if (client != NULL)
	{
		client->status = "offline";
		client->is_login = false;
	}
}


int Server::who(char* buffer, string username_email, int cli_sock)
{

	int index = 0;
	bool found = false;

	for (int i=0 ; i<users.size() ; ++i)
	{
		if (users[i]->is_login == false || users[i]->get_status() == "offline" || users[i]->get_username() == find_fd(cli_sock)->get_username())
			continue;

		char* ret1;
		char* ret2;
		const char* un = username_email.c_str();
		ret1 = strstr((char*)((users[i]->get_username()).c_str()), un);
		ret2 = strstr((char*)((users[i]->get_email()).c_str()), un);
		if (ret1 || ret2)
		{
			found = true;
			strncpy(&buffer[index],  (" "+users[i]->get_username() ).c_str() , PACKET_SIZE);
			index += users[i]->get_username().length() + 1;
			buffer[index] = '\n';
			index += 1;
		}
	}
	if (!found)
	{
		return 1;
	}
	else
	{
		buffer[index-1] = '\b' ;
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
		cout<<users[i]->username<<"'s Invitations is from : " ;
		for (int j = 0 ; j < users[i]->invitations.size(); j++)
			cout<<users[i]->invitations[j]<<" , " ;
		cout<<endl ;
	}
}










