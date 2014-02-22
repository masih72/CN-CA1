#include <iostream>
//#include <sys/types.h>
//#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "socket_manager.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

using namespace std;

Socket_manager::Socket_manager(Client* cli)
{
	this->client = cli;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		cerr << "error opening socket!" << endl;
		exit(0);
	}

	struct hostent *server;
	server = gethostbyname(cli->get_ip_addr());
	struct sockaddr_in srv_addr;
	bzero((char*) &srv_addr, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr(cli->get_ip_addr());
	bcopy((char*)server->h_addr, (char*)&srv_addr.sin_addr.s_addr, server->h_length);
	srv_addr.sin_port = htons(cli->get_port_num());

	//cout<<connect(sockfd, (struct sockaddr*) &srv_addr, sizeof(srv_addr)) ;
	if (connect(sockfd, (struct sockaddr*) &srv_addr, sizeof(srv_addr)) < 0)
	{
		cerr << "error connecting!" << endl;
		//exit(0);
	}

	while(1);
}


Socket_manager::~Socket_manager()
{

}
