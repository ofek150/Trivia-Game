#pragma once
#include "LoginManager.h"
#include "SqliteDataBase.h"

class LoginRequestHandler;
class MenuRequestHandler;

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
    MenuRequestHandler* createMenuRequestHandler() const;

    LoginManager& getLoginManager();
private:
    LoginManager& m_loginManager;
    IDatabase* m_database;


    // Private constructor to prevent instantiation from outside
    RequestHandlerFactory() : m_loginManager(LoginManager::getInstance()) {}
    // Private copy constructor to prevent cloning
    RequestHandlerFactory(const RequestHandlerFactory&);
};
