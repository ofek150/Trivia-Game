#include "Server.h"
#define EXIT_INPUT "EXIT"

void getInput()
{
	//get string in while(true) if input = exit ->exit else keep going 
	std::string input;
	while (true)
	{
		std::cin >> input;
		if (input == EXIT_INPUT)
		{
			std::unique_lock<std::mutex> exit_lock(exit_mtx);
			system("PAUSE");
			break;
		}
	}
}

int main()
{	
	Server myServer;

	std::thread server_thread(&Server::run, &myServer);
	server_thread.detach();

	getInput();
	return 0;
}

void Server::run()
{
	try
	{
		WSAInitializer wsaInit;
		m_communicator.startHandleRequests();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
}
