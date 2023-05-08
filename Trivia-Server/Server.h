#pragma once
#include "Communicator.h"
#pragma comment (lib, "ws2_32.lib")
#include "WSAInitializer.h"
#include "SqliteDataBase.h"
#include "RequestHandlerFactory.h"

class Server
{
public:

	void operator=(const Server&) = delete;

	// Public static function to get the singleton instance
	static Server& getInstance() {
		static Server instance;
		return instance;
	}

	void run();

private:
	void getInput();

	Communicator& m_communicator;
	IDatabase* m_database;
	RequestHandlerFactory& m_handlerFactory;


	// Private constructor to prevent instantiation from outside
	Server() : m_communicator(Communicator::getInstance()), m_handlerFactory(RequestHandlerFactory::getInstance()) {}

	// Private copy constructor to prevent cloning
	Server(const Server&);
};

