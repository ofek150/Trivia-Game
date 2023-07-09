#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"
#include "LoginRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() const
{
	auto requestHandler = new LoginRequestHandler();
	return requestHandler;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(const std::string& username) const
{
	auto requestHandler = new MenuRequestHandler(username);
	return requestHandler;
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(const std::string& username) const
{
	auto requestHandler = new RoomAdminRequestHandler(username);
	return requestHandler;
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(const std::string& username) const
{
	auto requestHandler = new RoomMemberRequestHandler(username);
	return requestHandler;
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(const std::string& username, Game& game) const
{
	auto requestHandler = new GameRequestHandler(username, game);
	return requestHandler;
}
