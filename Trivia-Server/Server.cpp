#include "Server.h"
#define EXIT_INPUT "EXIT"

void Server::getInput()
{
	//get string in while(true) if input = exit ->exit else keep going 
	std::string input;
	while (true)
	{
		std::cin >> input;
		if (input == EXIT_INPUT)
		{
			break;
		}
	}
}

void Server::run()
{
	try
	{
		WSAInitializer wsaInit;
		std::thread t_connector([&]() { m_communicator.startHandleRequests(); });
		t_connector.detach();

		getInput();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
}
