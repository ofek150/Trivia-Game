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

	/*int buffer_size = 57;
	const char* buffer2 = "\x02\x00\x00\x00\x32\x11\x2A\x23\x98\x23\xAB\xFF{\"username\":\"john_doe\",\"password\":\"p@ssw0rd\"}";
	LoginRequest loginRequest = JsonRequestPacketDeserializer::getInstance().deserializeLoginRequest(buffer2, buffer_size);*/

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
	SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);


	//Adding users to the clients map
	std::unique_lock<std::mutex> clients_lock(this->clients_mutex);
	LoginRequestHandler* loginRequestHandler = new LoginRequestHandler();

	this->m_clients.emplace(client_socket, loginRequestHandler);
	clients_lock.unlock();


	std::cout << "Client accepted. Server and client can speak" << std::endl;
	// the function that handle the conversation with the client
	std::thread clientThread(&Communicator::clientHandler, this, client_socket);
	clientThread.detach();


}

void Communicator::clientHandler(SOCKET clientSocket)
{
	try
	{
		// Receive the message from the client
		char buffer[1024] = { 0 };
		int bytesReceived = recv(clientSocket, buffer, 1024, 0);
		
		if (bytesReceived < 0) // Handling error in connection
		{
			throw std::exception("Error in connection. Logging out client...");
		}

		// Convert the received message to a std::string
		std::string receivedMessage(buffer, bytesReceived);


		std::cout << "Message from client: " << receivedMessage << std::endl;

		ErrorResponse errorResponse;
		errorResponse.errorMessage = "ERROR";
		std::vector<unsigned char> serializedErrorResponse = JsonRequestPacketSerializer::getInstance().serializeResponse(errorResponse);

		// Convert the response message to a UTF-8 encoded byte array
		std::vector<uint8_t> responseBytes(serializedErrorResponse.begin(), serializedErrorResponse.end());

		// Send the response message back to the client
		int bytesSent = send(clientSocket, reinterpret_cast<char*>(responseBytes.data()), responseBytes.size(), 0);
		std::cout << "Sent hello to client." << std::endl;
		
		if (bytesSent < 0) // Handling error in connection
		{
			throw std::exception("Error in connection. Logging out client...");
		}
		logOutClient(clientSocket);

	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		logOutClient(clientSocket);
		return;
	}
}

void Communicator::logOutClient(SOCKET clientSocket)
{
	try
	{
		std::lock_guard<std::mutex> clients_lock(clients_mutex);
		closesocket(clientSocket);
		delete m_clients[clientSocket];
		m_clients.erase(clientSocket);
		std::cout << "Removed a user from the connected users list" << std::endl;
	}
	catch (...) {}
}
