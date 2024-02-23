#pragma once
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(const LoggedUser user) : m_user(user), m_handlerFactory(RequestHandlerFactory::getInstance()), m_roomManager(RoomManager::getInstance()), m_statisticsManager(StatisticsManager::getInstance()) {};

	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	RequestResult handleRequest(const RequestInfo& requestInfo) const override;

	const LoggedUser& getUser() const;

private:
	RequestResult signout(const RequestInfo& requestInfo) const;
	RequestResult getRooms(const RequestInfo& requestInfo) const;
	RequestResult getPlayersInRoom(const RequestInfo& requestInfo) const;
	RequestResult getPersonalStats(const RequestInfo& requestInfo) const;
	RequestResult getHighScore(const RequestInfo& requestInfo) const;
	RequestResult joinRoom(const RequestInfo& requestInfo) const;
	RequestResult createRoom(const RequestInfo& requestInfo) const;

	bool isValidCategory(const std::string& targetCategory) const;

	LoggedUser m_user;
	RequestHandlerFactory& m_handlerFactory;
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;
};
