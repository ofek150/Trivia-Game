#pragma once
#include "GameManager.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory
{
public:
	void operator=(const RequestHandlerFactory&) = delete;

	// Public static function to get the singleton instance
	static RequestHandlerFactory& getInstance()
	{
		static RequestHandlerFactory instance;
		return instance;
	}

	LoginRequestHandler* createLoginRequestHandler() const;
	MenuRequestHandler* createMenuRequestHandler(const std::string& username) const;
	RoomAdminRequestHandler* createRoomAdminRequestHandler(const std::string& username) const;
	RoomMemberRequestHandler* createRoomMemberRequestHandler(const std::string& username) const;
	GameRequestHandler* createGameRequestHandler(const std::string& username, Game& game) const;

private:
	// Private constructor to prevent instantiation from outside
	RequestHandlerFactory()
	{
	};
	// Private copy constructor to prevent cloning
	RequestHandlerFactory(const RequestHandlerFactory&);
};
