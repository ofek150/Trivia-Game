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
	while (true)
	{
		try
		{
			std::string buffer = getMessage(clientSocket);
			
			std::cout << "Message from client: " << buffer << std::endl;
			

			//Extracting message code
			int message_code = getRequestCodeFromRequest(buffer);

			//Extracting the time of arrival
			time_t timestamp = getTimeStampFromRequest(buffer);


			if (message_code == RequestCodes::Login)
			{
				LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(buffer);
				//Handle Login request
				LoginResponse response;
				response.status = StatusCodes::LOGIN_SUCCESSFUL;
				std::vector<unsigned char> buffer = JsonRequestPacketSerializer::serializeResponse(response);
				std::string response_str(buffer.begin(), buffer.end());
				sendMessage(clientSocket, response_str);
			}
			else if (message_code == RequestCodes::Signup)
			{
				SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(buffer);
				//Handle Signup request
				SignupResponse response;
				response.status = StatusCodes::SIGNUP_SUCCESSFUL;
				std::vector<unsigned char> buffer = JsonRequestPacketSerializer::serializeResponse(response);
				std::string response_str(buffer.begin(), buffer.end());
				sendMessage(clientSocket, response_str);
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			logOutClient(clientSocket);
			return;
		}
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

time_t Communicator::getTimeStampFromRequest(std::string buffer)
{
	return *reinterpret_cast<time_t*>(&buffer[sizeof(int)]);
}

int Communicator::getRequestCodeFromRequest(std::string buffer)
{
	return static_cast<int>(buffer[0]);
}

void Communicator::sendMessage(const SOCKET socket, const std::string& message)
{
	const char* data = message.c_str();
	if (send(socket, data, message.size(), 0) == INVALID_SOCKET) throw std::exception("Error in connection. Logging out client...");
}

std::string Communicator::getMessage(const SOCKET socket)
{
	// Receive the message from the client
	char buffer[1024] = { 0 };
	unsigned int bytesReceived = recv(socket, buffer, 1024, 0);
	if(bytesReceived == INVALID_SOCKET) throw std::exception("Error in connection. Logging out client...");
	std::string receivedMessage(buffer, bytesReceived);

	return receivedMessage;

}
