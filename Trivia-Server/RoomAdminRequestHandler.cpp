#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "GameRequestHandler.h"

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
    return requestInfo.code == RequestCodes::CloseRoomRequestCode || requestInfo.code == RequestCodes::StartGameRequestCode
        || requestInfo.code == RequestCodes::GetRoomStateRequestCode;
}

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
	switch (requestInfo.code)
	{
	case RequestCodes::CloseRoomRequestCode:
		return closeRoom(requestInfo);
	case RequestCodes::StartGameRequestCode:
		return startGame(requestInfo);
	case RequestCodes::GetRoomStateRequestCode:
		return getRoomState(requestInfo);
	}
}

const LoggedUser& RoomAdminRequestHandler::getUser() const
{
    return m_user;
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo requestInfo) const
{
	RequestResult requestResult;
	CloseRoomResponse closeRoomResponse;
	requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	try {
		unsigned int roomId = m_roomManager.getRoomIdByUser(m_user);
		if (m_roomManager.getRoom(roomId).getAdmin().getUsername() != m_user.getUsername()) throw std::exception("You are not authorized to close the room!");
		m_roomManager.deleteRoom(roomId);
		closeRoomResponse.status = StatusCodes::SUCCESSFUL;

		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(closeRoomResponse);
	}
	catch (const std::exception& e)
	{
		requestResult = ErrorResult(e);
	}
	return requestResult;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo requestInfo) const
{
	RequestResult requestResult;
	StartGameResponse startGameResponse;
	try {

		unsigned int roomId = m_roomManager.getRoomIdByUser(m_user);
		if (m_roomManager.getRoom(roomId).getAdmin().getUsername() != m_user.getUsername()) throw std::exception("You are not authorized to start the game!");
		// Notify all users to start game
		m_roomManager.getRoom(roomId).startGame();
		requestResult.newHandler = m_handlerFactory.createGameRequestHandler(m_user.getUsername());
		startGameResponse.status = StatusCodes::SUCCESSFUL;

		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(startGameResponse);
	}
	catch (const std::exception& e)
	{
		requestResult = ErrorResult(e);
	}
	return requestResult;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo requestInfo) const
{
	RequestResult requestResult;
	GetRoomStateResponse getRoomStateResponse;
	try {

		unsigned int roomId = m_roomManager.getRoomIdByUser(m_user);
		RoomData roomData = m_roomManager.getRoom(roomId).getRoomData();
		getRoomStateResponse.status = StatusCodes::SUCCESSFUL;
		getRoomStateResponse.hasGameBegun = roomData.isActive;
		getRoomStateResponse.answerTimeOut = roomData.timePerQuestion;
		getRoomStateResponse.questionCount = roomData.numOfQuestionsInGame;
		std::vector<std::string> players;
		std::vector<LoggedUser> users = m_roomManager.getRoom(roomId).getAllUsers();
		if (getRoomStateResponse.hasGameBegun)
			requestResult.newHandler = m_handlerFactory.createGameRequestHandler(m_user.getUsername(), GameManager::getInstance().createGame(m_roomManager.getRoom(roomId)));
		else
			requestResult.newHandler = m_handlerFactory.createRoomAdminRequestHandler(m_user.getUsername());

		for (auto user : users)
		{
			players.push_back(user.getUsername());
		}
		getRoomStateResponse.players = players;

		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(getRoomStateResponse);
	}
	catch (const std::exception& e)
	{
		requestResult = ErrorResult(e);
	}

	return requestResult;
}
