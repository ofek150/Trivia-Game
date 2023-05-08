#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"
#include "LoginRequestHandler.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() const
{
    LoginRequestHandler* requestHandler = new LoginRequestHandler();
    return requestHandler;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler() const
{
    MenuRequestHandler* requestHandler = new MenuRequestHandler();
    return requestHandler;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return m_loginManager;
}
