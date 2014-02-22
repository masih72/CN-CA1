#include <cstdlib>
#include "client.h"

using namespace std;

int main(int argc, char* argv[])
{
	Client client(argv[1], atoi(argv[2]));
	client.run();

	return 0;
}
