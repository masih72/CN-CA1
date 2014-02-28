#ifndef USER_H
#define USER_H

class Packet_manager;
class Socket_manager;
class Server;

#include <string>
#include <vector>
#include "packet_manager.h"
#include "socket_manager.h"
#include "server.h"

using namespace std ;

class User
{
public:

	User(string username, string password, string email, int client_fd) ;
	User() ;
	vector <string> invitations ;
	vector <string> friends ;
	string get_username() { return this->username ; }
	string get_password() { return this->password ; }
	string get_email()  { return this->email ; }
	string get_status() { return status ; }
	bool get_is_login() { return is_login ; }
	int get_client_fd() { return client_fd ; }
	string get_selected_friend() { return selected_friend; }

	void set_selected_friend(string un) { selected_friend = un; }

	bool has_friend(string username);

	friend class Server ;

private:
	bool is_login ;
	int client_fd ;
	string username ;
	string password ;
	string email ;
	string status ;
	string selected_friend;
};

#endif
