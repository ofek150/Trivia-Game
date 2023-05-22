#include "MenuRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "StatusCodes.h"

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	return requestInfo.code == RequestCodes::CreateRoomRequestCode || requestInfo.code == RequestCodes::GetRoomsRequestCode
		|| requestInfo.code == RequestCodes::GetPlayersInRoomRequestCode || requestInfo.code == RequestCodes::JoinRoomRequestCode
		|| requestInfo.code == RequestCodes::GetHighScoreRequestCode || requestInfo.code == RequestCodes::GetHighScoreRequestCode
		|| requestInfo.code == RequestCodes::LogoutRequestCode;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
	switch (requestInfo.code)
	{
	case RequestCodes::CreateRoomRequestCode:
		return createRoom(requestInfo);
	case RequestCodes::GetRoomsRequestCode:
		return getRooms(requestInfo);
	case RequestCodes::GetPlayersInRoomRequestCode:
		return getPlayersInRoom(requestInfo);
	case RequestCodes::JoinRoomRequestCode:
		return joinRoom(requestInfo);
	case RequestCodes::GetHighScoreRequestCode:
		return getHighScore(requestInfo);
	case RequestCodes::LogoutRequestCode:
		return signout(requestInfo);
	}
}

const LoggedUser& MenuRequestHandler::getUser() const
{
	return m_user;
}

RequestResult MenuRequestHandler::signout(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;
	LogoutResponse logoutResponse;
	requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	try {
		LoginManager& loginManager = m_handlerFactory.getLoginManager();
		loginManager.logout(m_user.getUsername());

		logoutResponse.status = StatusCodes::SUCCESSFUL;
		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(logoutResponse);
	}
	catch (const std::exception& e)
	{
		ErrorResponse errorResponse;
		errorResponse.errorMessage = e.what();
		std::cerr << e.what() << std::endl;
		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(errorResponse);
	}

	return requestResult;
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;
	GetRoomsResponse getRoomsResponse;
	requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	try {
		getRoomsResponse.status = StatusCodes::SUCCESSFUL;
		getRoomsResponse.rooms = m_roomManager.getRoomsDatas();
		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(getRoomsResponse);
	}
	catch (const std::exception& e)
	{
		ErrorResponse errorResponse;
		errorResponse.errorMessage = e.what();
		std::cerr << e.what() << std::endl;
		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(errorResponse);
	}

	return requestResult;
}

RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;
	GetPlayersInRoomResponse getPlayersInRoomResponse;
	requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	try {
		std::vector<std::string> players;
		std::map<unsigned int, Room> rooms = m_roomManager.getRooms();
		
		GetPlayersInRoomRequest getPlayersInRoomRequest = JsonRequestPacketDeserializer::getInstance().deserializeGetPlayersInRoomRequest(requestInfo.buffer);
		std::vector<LoggedUser> users =  m_roomManager.getRoom(getPlayersInRoomRequest.roomId).getAllUsers();
		for (auto user : users)
		{
			players.push_back(user.getUsername());
		}
		getPlayersInRoomResponse.players = players;

		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(getPlayersInRoomResponse);
	}
	catch (const std::exception& e)
	{
		ErrorResponse errorResponse;
		errorResponse.errorMessage = e.what();
		std::cerr << e.what() << std::endl;
		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(errorResponse);
	}

	return requestResult;
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;
	GetPersonalStatsResponse getPersonalStatsResponse;
	requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	try {
		getPersonalStatsResponse.statistics = m_statisticsManager.getUserStatistics(m_user.getUsername());
		getPersonalStatsResponse.status = StatusCodes::SUCCESSFUL;

		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(getPersonalStatsResponse);
	}
	catch (const std::exception& e)
	{
		ErrorResponse errorResponse;
		errorResponse.errorMessage = e.what();
		std::cerr << e.what() << std::endl;
		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(errorResponse);
	}

	return requestResult;
}

RequestResult MenuRequestHandler::getHighScore(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;
	GetHighScoreRoomResponse getHighScoreResponse;
	requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	try {
		getHighScoreResponse.statistics = m_statisticsManager.getHighScore();
		getHighScoreResponse.status = StatusCodes::SUCCESSFUL;

		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(getHighScoreResponse);
	}
	catch (const std::exception& e)
	{
		ErrorResponse errorResponse;
		errorResponse.errorMessage = e.what();
		std::cerr << e.what() << std::endl;
		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(errorResponse);
	}

	return requestResult;
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;
	JoinRoomResponse joinRoomResponse;
	requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	try {
		std::vector<std::string> players;
		std::map<unsigned int, Room> rooms = m_roomManager.getRooms();
		JoinRoomRequest joinRoomRequest = JsonRequestPacketDeserializer::getInstance().deserializeJoinRoomRequest(requestInfo.buffer);
		LoggedUser user(m_user);
		rooms[joinRoomRequest.roomId].addUser(user);
		joinRoomResponse.status = StatusCodes::SUCCESSFUL;

		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(joinRoomResponse);
	}
	catch (const std::exception& e)
	{
		ErrorResponse errorResponse;
		errorResponse.errorMessage = e.what();
		std::cerr << e.what() << std::endl;
		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(errorResponse);
	}

	return requestResult;
}

RequestResult MenuRequestHandler::createRoom(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;
	CreateRoomResponse createRoomResponse;
	requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	try {
		std::vector<std::string> players;
		int roomCount = m_roomManager.getRooms().size();
		CreateRoomRequest createRoomRequest = JsonRequestPacketDeserializer::getInstance().deserializeCreateRoomRequest(requestInfo.buffer);
		LoggedUser user(m_user);
		RoomData roomData;
		roomData.name = createRoomRequest.roomName;
		roomData.timePerQuestion = createRoomRequest.answerTimeout;
		roomData.numOfQuestionsInGame = createRoomRequest.questionCount;
		roomData.maxPlayers = createRoomRequest.maxUsers;
		roomData.id = roomCount;

		m_roomManager.createRoom(user, roomData);
		createRoomResponse.status = StatusCodes::SUCCESSFUL;

		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(createRoomResponse);
	}
	catch (const std::exception& e)
	{
		ErrorResponse errorResponse;
		errorResponse.errorMessage = e.what();
		std::cerr << e.what() << std::endl;
		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(errorResponse);
	}

	return requestResult;
}
