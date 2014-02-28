#include <iostream>
#include <vector> 
#include "user.h"

using namespace std ;

/*vector <string> User::invitations ;
vector <string> User::friends ;*/


User::User (string username, string password, string email, int client_fd)
{
	this->username = username ;
	this->password = password ;
	this->email = email ;
	this->is_login = false ;
	this->status = "offline" ;
	this->client_fd = client_fd ;
	this->selected_friend = "";
}


bool User::has_friend(string username)
{
	for (int i=0 ; i<friends.size() ; ++i)
		if (friends[i] == username)
			return true;

	return false;
}
