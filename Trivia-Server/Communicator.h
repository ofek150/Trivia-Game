#pragma once
#include <WinSock2.h>
#include <map>
#include <mutex>
#include "MenuRequestHandler.h"
#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "RoomMemberRequestHandler.h"
#include  "RoomAdminRequestHandler.h"

#define SERVER_PORT 6969


class Communicator
{
public:
	void operator=(const Communicator&) = delete;

	// Public static function to get the singleton instance
	static Communicator& getInstance()
	{
		static Communicator instance;
		return instance;
	}


	~Communicator();
	void startHandleRequests();

private:
	void bindAndListen();
	void handleNewClient();
	void clientHandler(SOCKET clientSocket);
	void logOutClient(SOCKET clientSocket); // Removes a client from the clients map and closes socket

	//Helper functions
	int getRequestCodeFromRequest(SOCKET socket); // Parses the request code from the buffer and returns it
	void sendMessage(SOCKET socket, const std::vector<unsigned char>& message) const; // Send a message to the client
	RequestInfo getRequest(SOCKET socket); // Gets a request from the client

	void insertNewClient(SOCKET clientSocket);
	void sendErrorResponse(SOCKET clientSocket);

	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	std::mutex clients_mutex;

	RequestHandlerFactory& m_handlerFactory;


	// Private constructor to prevent instantiation from outside
	Communicator() : m_handlerFactory(RequestHandlerFactory::getInstance())
	{
	}

	// Private copy constructor to prevent cloning
	Communicator(const Communicator&);
};
