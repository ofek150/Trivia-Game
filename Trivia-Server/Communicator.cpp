#include "Communicator.h"

Communicator::~Communicator()
{
	try
	{
		// Delete all the IRequestHandlers from the memory
		for (auto& client : m_clients)
		{
			delete client.second;
		}

		closesocket(m_serverSocket);
	}
	catch (...) {}
}

void Communicator::startHandleRequests()
{
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");

	bindAndListen();
}

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(SERVER_PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << SERVER_PORT << std::endl;

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		std::cout << "Waiting for client connection request" << std::endl;
		handleNewClient();
	}
}

void Communicator::handleNewClient()
{
	// this accepts the client and create a specific socket from server to this client
	// the process will not continue until a client connects to the server
	SOCKET clientSocket = accept(m_serverSocket, NULL, NULL);
	if (clientSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);
	insertNewClient(clientSocket);

	std::cout << "Client accepted. Server and client can speak" << std::endl;
	// the function that handle the conversation with the client
	std::thread clientThread(&Communicator::clientHandler, this, clientSocket);
	clientThread.detach();


}

void Communicator::clientHandler(SOCKET clientSocket)
{
	while (true)
	{
		try
		{
			RequestInfo requestInfo = getRequest(clientSocket);

			IRequestHandler* handler = m_clients[clientSocket];
			if (handler->isRequestRelevant(requestInfo))
			{
				RequestResult requestResult = handler->handleRequest(requestInfo);
				if (requestResult.responseBuffer[0] == ResponseCodes::ErrorResponseCode)
				{
					requestResult.newHandler = m_clients[clientSocket];
				}
				else
				{
					delete handler;
					std::unique_lock<std::mutex> clients_lock(this->clients_mutex);
					m_clients[clientSocket] = requestResult.newHandler;
					clients_lock.unlock();
				}
				sendMessage(clientSocket, requestResult.responseBuffer);
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			logOutClient(clientSocket);
			return;
		}
		catch (...)
		{
			logOutClient(clientSocket);
			return;
		}
	}
}

void Communicator::logOutClient(SOCKET clientSocket)
{
	try
	{
		closesocket(clientSocket);

		if (m_clients[clientSocket] && dynamic_cast<LoginRequestHandler*>(m_clients[clientSocket]))
		{
			RequestInfo requestInfo;
			LoginManager::getInstance().logout(m_clients[clientSocket]->getUser().getUsername());
		}

		std::lock_guard<std::mutex>clients_lock(this->clients_mutex);
		delete m_clients[clientSocket];
		m_clients.erase(clientSocket);
		std::cout << "Removed a user from the connected users list" << std::endl;
	}
	catch (...) {}
}

int Communicator::getRequestCodeFromRequest(const SOCKET socket)
{
	// Receive the message from the client
	char buffer[1] = { 0 };
	int bytesReceived = recv(socket, buffer, 1, 0);
	if (bytesReceived < 0) throw std::exception("Error in connection. Logging out client...");
	if (bytesReceived == 0) throw std::exception("Client has closed the connection");
	return static_cast<int>(buffer[0]);
}

void Communicator::sendMessage(const SOCKET socket, const std::vector<unsigned char>& message) const
{
	const unsigned char* buffer = reinterpret_cast<const unsigned char*>(message.data());

	if(send(socket, reinterpret_cast<const char*>(buffer), message.size(), 0) == SOCKET_ERROR) throw std::exception("Error in connection. Logging out client...");
}

RequestInfo Communicator::getRequest(const SOCKET socket)
{
	RequestInfo requestInfo;
	requestInfo.code = getRequestCodeFromRequest(socket);

	// Receive the message from the client
	char data_size_buffer[4] = { 0 };
	int bytesReceived = recv(socket, data_size_buffer, 4, 0);
	if (bytesReceived < 0) throw std::exception("Error in connection. Logging out client...");

	int data_size = ntohl(*reinterpret_cast<uint32_t*>(data_size_buffer));

	char* buffer = new char[data_size];
	int bytesReceived2 = recv(socket, buffer, data_size, 0);
	if (bytesReceived2 < 0) throw std::exception("Error in connection. Logging out client...");

	time_t current_time;
	time(&current_time);
	requestInfo.arrival_time = current_time;
	requestInfo.buffer = std::vector<unsigned char>(buffer, buffer + data_size);
	
	delete[] buffer;

	return requestInfo;
}

void Communicator::insertNewClient(SOCKET clientSocket)
{
	std::lock_guard<std::mutex>clients_lock(this->clients_mutex);
	LoginRequestHandler* loginRequestHandler = new LoginRequestHandler();
	m_clients[clientSocket] = loginRequestHandler;
}

void Communicator::sendErrorResponse(SOCKET clientSocket)
{
	ErrorResponse errorResponse;
	errorResponse.errorMessage = "Invalid request code";
	sendMessage(clientSocket, JsonRequestPacketSerializer::getInstance().serializeResponse(errorResponse));
}
