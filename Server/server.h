#ifndef SERVER_H
#define SERVER_H

class Packet_manager;
class Socket_manager;
class User;

#include <string>
#include <vector>
#include "packet_manager.h"
#include "socket_manager.h"
#include "user.h"

using namespace std ;

class Server
{
public:
	Server(int port_num);
	virtual ~Server();

	void run();
	static vector <User*> users ; 
	int get_port_num() { return port_num; }
	Packet_manager* get_packet_manager() { return packet_manager; }
	int register_user (string username, string password, string email) ;
	int login_user (string username, string password) ;
	User* find_username (string name) ;
	bool check_user_pass (string name, string pass) ;
	bool is_registered(string name) ;

	friend class User ;


private:
	int port_num;
	Packet_manager* packet_manager;
	Socket_manager* socket_manager;
};



#endif
