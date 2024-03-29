#include "MenuRequestHandler.h"
#include "LoginRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "StatusCodes.h"

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	return requestInfo.code == CreateRoomRequestCode || requestInfo.code == GetRoomsRequestCode
		|| requestInfo.code == GetPlayersInRoomRequestCode || requestInfo.code == JoinRoomRequestCode
		|| requestInfo.code == GetHighScoreRequestCode || requestInfo.code == GetPersonalStatsRequestCode
		|| requestInfo.code == LogoutRequestCode;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
	switch (requestInfo.code)
	{
	case CreateRoomRequestCode:
		return createRoom(requestInfo);
	case GetRoomsRequestCode:
		return getRooms(requestInfo);
	case GetPlayersInRoomRequestCode:
		return getPlayersInRoom(requestInfo);
	case JoinRoomRequestCode:
		return joinRoom(requestInfo);
	case GetHighScoreRequestCode:
		return getHighScore(requestInfo);
	case GetPersonalStatsRequestCode:
		return getPersonalStats(requestInfo);
	case LogoutRequestCode:
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
	requestResult.newHandler = requestResult.newHandler = m_handlerFactory.createLoginRequestHandler();

	try
	{
		LoginManager& loginManager = LoginManager::getInstance();
		loginManager.logout(m_user.getUsername());

		logoutResponse.status = SUCCESSFUL;
		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(logoutResponse);
	}
	catch (const std::exception& e)
	{
		requestResult = ErrorResult(e);
	}

	return requestResult;
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;
	GetRoomsResponse getRoomsResponse;
	requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	try
	{
		getRoomsResponse.status = SUCCESSFUL;
		getRoomsResponse.rooms = m_roomManager.getRoomsDatas();
		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(getRoomsResponse);
	}
	catch (const std::exception& e)
	{
		requestResult = ErrorResult(e);
	}

	return requestResult;
}

RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;
	GetPlayersInRoomResponse getPlayersInRoomResponse;
	requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	try
	{
		std::vector<std::string> players;
		GetPlayersInRoomRequest getPlayersInRoomRequest = JsonRequestPacketDeserializer::getInstance().
			deserializeGetPlayersInRoomRequest(requestInfo.buffer);
		std::vector<LoggedUser> users = m_roomManager.getRoom(getPlayersInRoomRequest.roomId).getAllUsers();
		for (auto user : users)
		{
			players.push_back(user.getUsername());
		}
		getPlayersInRoomResponse.players = players;

		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(
			getPlayersInRoomResponse);
	}
	catch (const std::exception& e)
	{
		requestResult = ErrorResult(e);
	}

	return requestResult;
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;
	GetPersonalStatsResponse getPersonalStatsResponse;
	requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	try
	{
		getPersonalStatsResponse.statistics = m_statisticsManager.getUserStatistics(m_user.getUsername());
		getPersonalStatsResponse.status = SUCCESSFUL;

		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(
			getPersonalStatsResponse);
	}
	catch (const std::exception& e)
	{
		requestResult = ErrorResult(e);
	}

	return requestResult;
}

RequestResult MenuRequestHandler::getHighScore(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;
	GetHighScoreRoomResponse getHighScoreResponse;
	requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	try
	{
		getHighScoreResponse.statistics = m_statisticsManager.getHighScore();
		getHighScoreResponse.status = SUCCESSFUL;

		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(
			getHighScoreResponse);
	}
	catch (const std::exception& e)
	{
		requestResult = ErrorResult(e);
	}

	return requestResult;
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;
	JoinRoomResponse joinRoomResponse;
	requestResult.newHandler = m_handlerFactory.createRoomMemberRequestHandler(m_user.getUsername());
	try
	{
		std::vector<std::string> players;
		JoinRoomRequest joinRoomRequest = JsonRequestPacketDeserializer::getInstance().deserializeJoinRoomRequest(
			requestInfo.buffer);

		m_roomManager.joinRoom(m_user, joinRoomRequest.roomId);
		joinRoomResponse.status = SUCCESSFUL;

		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(joinRoomResponse);
	}
	catch (const std::exception& e)
	{
		requestResult = ErrorResult(e);
	}

	return requestResult;
}

RequestResult MenuRequestHandler::createRoom(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;
	CreateRoomResponse createRoomResponse;
	requestResult.newHandler = m_handlerFactory.createRoomAdminRequestHandler(m_user.getUsername());
	try
	{
		std::vector<std::string> players;
		CreateRoomRequest createRoomRequest = JsonRequestPacketDeserializer::getInstance().deserializeCreateRoomRequest(requestInfo.buffer);

		if (!isValidCategory(createRoomRequest.category)) throw std::exception("Invalid category!");

		RoomData roomData;
		roomData.name = createRoomRequest.roomName;
		roomData.timePerQuestion = createRoomRequest.answerTimeout;
		roomData.numOfQuestionsInGame = createRoomRequest.questionCount;
		roomData.maxPlayers = createRoomRequest.maxUsers;
		roomData.id = m_roomManager.getIdCounter();
		roomData.isActive = 0;
		roomData.category = createRoomRequest.category;

		m_roomManager.createRoom(m_user, roomData);
		createRoomResponse.status = SUCCESSFUL;
		createRoomResponse.roomId = roomData.id;

		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(createRoomResponse);
	}
	catch (const std::exception& e)
	{
		requestResult = ErrorResult(e);
	}

	return requestResult;
}

bool MenuRequestHandler::isValidCategory(const std::string& targetCategory) const
{
	const std::vector<std::string> categories = {"General", "Geography", "Sports"};
	auto it = std::find(categories.begin(), categories.end(), targetCategory);
	return it != categories.end();
}
