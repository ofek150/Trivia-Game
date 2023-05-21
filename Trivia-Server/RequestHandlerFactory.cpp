#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"
#include "LoginRequestHandler.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() const
{
    LoginRequestHandler* requestHandler = new LoginRequestHandler();
    return requestHandler;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(const std::string& username) const
{
    MenuRequestHandler* requestHandler = new MenuRequestHandler(username);
    return requestHandler;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return m_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    return m_roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    return m_statisticsManager;
}
