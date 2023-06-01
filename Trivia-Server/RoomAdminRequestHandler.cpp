#include "MenuRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "RoomAdminRequestHandler.h"

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
		if (roomId == -1) throw std::exception("The user isn't in any room!");
		if (m_roomManager.getRoom(roomId).getAdmin().getUsername() != m_user.getUsername()) throw std::exception("You are not authorized to close the room!");
		closeRoomResponse.status = StatusCodes::SUCCESSFUL;

		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(closeRoomResponse);
	}
	catch (const std::exception& e)
	{
		requestResult = ErrorResult(e);
	}

}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo requestInfo) const
{
	RequestResult requestResult;
	StartGameResponse startGameResponse;
	// Change to game request handler
	requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	try {

		unsigned int roomId = m_roomManager.getRoomIdByUser(m_user);
		if (m_roomManager.getRoom(roomId).getAdmin().getUsername() != m_user.getUsername()) throw std::exception("You are not authorized to close the room!");
		// Notify all users to start game
		m_roomManager.getRoom(roomId).startGame();
		startGameResponse.status = StatusCodes::SUCCESSFUL;

		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(startGameResponse);
	}
	catch (const std::exception& e)
	{
		requestResult = ErrorResult(e);
	}
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo requestInfo) const
{
	RequestResult requestResult;
	GetRoomStateResponse getRoomStateResponse;
	// Change to game request handler
	requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	try {

		unsigned int roomId = m_roomManager.getRoomIdByUser(m_user);
		RoomData roomData = m_roomManager.getRoom(roomId).getRoomData();
		getRoomStateResponse.status = StatusCodes::SUCCESSFUL;
		getRoomStateResponse.hasGameBegun = roomData.isActive;
		getRoomStateResponse.answerTimeOut = roomData.timePerQuestion;
		getRoomStateResponse.questionCount = roomData.numOfQuestionsInGame;
		std::vector<std::string> players;
		std::vector<LoggedUser> users = m_roomManager.getRoom(roomId).getAllUsers();
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
}
