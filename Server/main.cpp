#include <cstdlib>
#include "server.h"

using namespace std;

int main(int argc, char* argv[])
{
	Server server(atoi(argv[1]));
	server.run();

	return 0;
}