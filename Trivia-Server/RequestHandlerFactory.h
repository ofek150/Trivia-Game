#pragma once
#include "LoginManager.h"
#include "SqliteDataBase.h"
#include "StatisticsManager.h"
#include "RoomManager.h";

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;

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
    //RoomMemberRequestHandler* createRoomMemberRequestHandler(const std::string& username) const;


    LoginManager& getLoginManager();
    RoomManager& getRoomManager();
    StatisticsManager& getStatisticsManager();
private:
    LoginManager& m_loginManager;
    RoomManager& m_roomManager;
    StatisticsManager& m_statisticsManager;
    IDatabase* m_database;


    // Private constructor to prevent instantiation from outside
    RequestHandlerFactory() : m_loginManager(LoginManager::getInstance()), m_roomManager(RoomManager::getInstance()), m_statisticsManager(StatisticsManager::getInstance()), m_database(&SqliteDataBase::getInstance()) {}
    // Private copy constructor to prevent cloning
    RequestHandlerFactory(const RequestHandlerFactory&);
};
