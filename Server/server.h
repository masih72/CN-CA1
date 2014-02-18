#ifndef SERVER_H
#define SERVER_H


class Server
{
public:
	Server(int port_num);
	virtual ~Server();
	void run();

private:
	int port_num;
};


#endif