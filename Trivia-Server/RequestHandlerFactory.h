#pragma once
#include "LoginManager.h"
#include "SqliteDataBase.h"
#include "StatisticsManager.h"
#include "RoomManager.h";
#include "GameManager.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;

class RequestHandlerFactory
{
public:
    void operator=(const RequestHandlerFactory&) = delete;

    // Public static function to get the singleton instance
    static RequestHandlerFactory& getInstance() {
        static RequestHandlerFactory instance;
        return instance;
    }

    LoginRequestHandler* createLoginRequestHandler() const;
    MenuRequestHandler* createMenuRequestHandler(const std::string& username) const;
    RoomAdminRequestHandler* createRoomAdminRequestHandler(const std::string& username) const;
    RoomMemberRequestHandler* createRoomMemberRequestHandler(const std::string& username) const;

private:
    // Private constructor to prevent instantiation from outside
    RequestHandlerFactory() {};
    // Private copy constructor to prevent cloning
    RequestHandlerFactory(const RequestHandlerFactory&);
};
