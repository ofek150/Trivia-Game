#pragma once
#include "Communicator.h"
#pragma comment (lib, "ws2_32.lib")
#include "WSAInitializer.h"



class Server
{
public:
	void run();

private:
	Communicator m_communicator;
};

