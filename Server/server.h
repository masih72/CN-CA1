#ifndef SERVER_H
#define SERVER_H

class Socket_manager;

#include "socket_manager.h"

class Server
{
public:
	Server(int port_num);
	virtual ~Server();

	void run();

	int get_port_num() { return port_num; }

private:
	int port_num;
	Socket_manager* socket_manager;
};


#endif
