#pragma once
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
    MenuRequestHandler(const std::string& username) : m_handlerFactory(RequestHandlerFactory::getInstance()), m_roomManager(RoomManager::getInstance()), m_statisticsManager(StatisticsManager::getInstance()), IRequestHandler(username) {};

    bool isRequestRelevant(const RequestInfo& requestInfo) const override;
    RequestResult handleRequest(const RequestInfo& requestInfo) const override;

private:
    RequestResult signout(const RequestInfo& requestInfo) const;
    RequestResult getRooms(const RequestInfo& requestInfo) const;
    RequestResult getPlayersInRoom(const RequestInfo& requestInfo) const;
    RequestResult getPersonalStats(const RequestInfo& requestInfo) const;
    RequestResult getHighScore(const RequestInfo& requestInfo) const;
    RequestResult joinRoom(const RequestInfo& requestInfo) const;
    RequestResult createRoom(const RequestInfo& requestInfo) const;

    RequestHandlerFactory& m_handlerFactory;
    RoomManager& m_roomManager;
    StatisticsManager& m_statisticsManager;
};
