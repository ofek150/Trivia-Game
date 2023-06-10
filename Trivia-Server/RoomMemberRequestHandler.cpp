#include "MenuRequestHandler.h"
#include "RoomMemberRequestHandler.h"

bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	return requestInfo.code == RequestCodes::LeaveRoomRequestCode || requestInfo.code == RequestCodes::GetRoomStateRequestCode;
}

RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
	switch (requestInfo.code)
	{
	case RequestCodes::LeaveRoomRequestCode:
		return leaveRoom(requestInfo);
	case RequestCodes::GetRoomStateRequestCode:
		return getRoomState(requestInfo);
	}
}

const LoggedUser& RoomMemberRequestHandler::getUser() const
{
	return m_user;
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo requestInfo) const
{
	RequestResult requestResult;
	LeaveRoomResponse leaveRoomResponse;
	requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());
	try {
		m_roomManager.leaveRoom(m_user);
		leaveRoomResponse.status = StatusCodes::SUCCESSFUL;
		requestResult.responseBuffer = JsonRequestPacketSerializer::getInstance().serializeResponse(leaveRoomResponse);
	}
	catch (const std::exception& e)
	{
		requestResult = ErrorResult(e);
	}
	return requestResult;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo requestInfo) const
{
	RequestResult requestResult;
	GetRoomStateResponse getRoomStateResponse;
	requestResult.newHandler = m_handlerFactory.createRoomMemberRequestHandler(m_user.getUsername());
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

	return requestResult;
}
