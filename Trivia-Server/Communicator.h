#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <string>
#include <thread>
#include <chrono>
#include <exception>
#include <mutex>
#include <iostream>
#include <string>
#include "LoginRequestHandler.h"
#include "StatusCodes.h"


#define SERVER_PORT 6969


class Communicator
{
public:
	~Communicator();
	void startHandleRequests();
private:
	void bindAndListen();
	void handleNewClient();
	void clientHandler(SOCKET clientSocket);
	void logOutClient(SOCKET clientSocket); // Removes a client from the clients map and closes socket

	//Helper functions
	time_t getTimeStampFromRequest(std::string buffer); // Parses the timestamp from the buffer and returns it
	int getRequestCodeFromRequest(std::string buffer); // Parses the request code from the buffer and returns it
	void sendMessage(const SOCKET socket, const std::string& message); // Send a message to the client
	std::string getMessage(const SOCKET socket); // Gets a message from the client.

	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	std::mutex clients_mutex;

};

