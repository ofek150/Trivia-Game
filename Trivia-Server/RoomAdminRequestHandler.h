#pragma once
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(const LoggedUser user) : m_user(user), m_handlerFactory(RequestHandlerFactory::getInstance()), m_roomManager(RoomManager::getInstance()) {};

	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	RequestResult handleRequest(const RequestInfo& requestInfo) const override;

	const LoggedUser& getUser() const;

private:
	RequestResult closeRoom(RequestInfo requestInfo) const;
	RequestResult startGame(RequestInfo requestInfo) const;
	RequestResult getRoomState(RequestInfo requestInfo) const;

	LoggedUser m_user;
	RequestHandlerFactory& m_handlerFactory;
	RoomManager& m_roomManager;
};
