#include "Server.h"

std::mutex exit_mtx;
std::condition_variable exit_cv;
bool exit_flag = false;

void getInput()
{
	//get string in while(true) if input = exit ->exit else keep going 
	std::string input;
	while (true)
	{
		std::cin >> input;
		if (input == "EXIT")
		{
			std::unique_lock<std::mutex> exit_lock(exit_mtx);
			exit_flag = true;
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
