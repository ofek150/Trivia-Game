#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <map>
#include <string>
#include <thread>
#include <chrono>
#include <queue>
#include <exception>
#include <mutex>
#include <iostream>
#include <set>
#include "LoginRequestHandler.h"

#define SERVER_PORT 6969


class Communicator
{
public:
	~Communicator();
	void startHandleRequests();
private:
	void bindAndListen();
	void handleNewClient();
	void clientHandler(SOCKET clientSocket); // Handles the client
	void logOutUser(SOCKET clientSocket);

	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	std::mutex clients_mutex;

};

