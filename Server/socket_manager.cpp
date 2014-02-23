#include <iostream>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "socket_manager.h"

using namespace std;

Socket_manager::Socket_manager(Server* srv)
{
	this->server = srv;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		cerr << "error opening socket!" << endl;
		exit(1);
	}
	this->set_accept_sockfd(sockfd);

	struct sockaddr_in srv_addr;
	bzero((char*) &srv_addr, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = INADDR_ANY;
	srv_addr.sin_port = htons(this->server->get_port_num());

	if (::bind(sockfd, (struct sockaddr*) &srv_addr, sizeof(srv_addr)) < 0)
	{
		cerr << "error binding socket!" << endl;
		exit(1);
	}

	listen(sockfd, 1024);

	this->accept_thread = new thread(Socket_manager::accept_connection, this);
}


Socket_manager::~Socket_manager()
{
	delete this->accept_thread;
	for (int i=0 ; i<this->receiver_threads.size() ; ++i)
		delete this->receiver_threads[i];
}


void Socket_manager::accept_connection(Socket_manager* socket_manager)
{
	struct sockaddr_in cli_addr;
	socklen_t clilen = sizeof(cli_addr);
	while(1)
	{
		int cli_sock = accept(socket_manager->get_accept_sockfd(), (struct sockaddr*) &cli_addr, &clilen);
		if (cli_sock < 0)
		{
			cerr << "error accepting!" << endl;
			exit(1);
		}

		thread* receiver_thread = new thread(Socket_manager::receive, socket_manager, cli_sock);
		socket_manager->receiver_threads.push_back(receiver_thread);
	}
}


void Socket_manager::receive(Socket_manager* socket_manager, int cli_sock)
{
	char buffer[PACKET_SIZE];

	while(1)
	{
		bzero(buffer, sizeof(buffer));

		cout << "waiting on a packet..." << endl;
		while( read(cli_sock, buffer, sizeof(buffer)-1) < 0);

		cout << "decoding packet..." << endl;
		socket_manager->get_server()->get_packet_manager()->decode(buffer);
	}
}
