#ifndef SOCKET_MANAGER_H
#define SOCKET_MANAGER_H

class Server;

#include <vector>
#include <thread>
#include "server.h"

using namespace std;

class Socket_manager
{
public:
	Socket_manager(Server* srv);
	virtual ~Socket_manager();

	static void accept_connection(Socket_manager* socket_manager);
	static void receive(Socket_manager* socket_manager, int cli_sock);

	int get_accept_sockfd() { return accept_sockfd; }
	Server* get_server() { return server; }

	void set_accept_sockfd(int sockfd) { this->accept_sockfd = sockfd; }

private:
	int accept_sockfd;
	thread* accept_thread;
	vector<thread*> receiver_threads;
	Server* server;
};

#endif
