#include "Server.h"

int main()
{
	Server& myServer = Server::getInstance();
	myServer.run();
	return 0;
}
