#pragma once
#include "SqliteDataBase.h"
#include <vector>
#include <mutex>
#include "LoggedUser.h"

class LoginManager
{
public:
	void operator=(const LoginManager&) = delete;

	// Public static function to get the singleton instance
	static LoginManager& getInstance()
	{
		static LoginManager instance;
		return instance;
	}


	void signup(std::string username, std::string password, std::string email);
	void login(std::string username, std::string password);
	void logout(std::string username);

private:
	bool isUserInLoggedUsers(const std::string& username);

	std::vector<LoggedUser> m_loggedUsers;
	std::mutex loggedUsers_mutex;
	IDatabase* m_database;


	// Private constructor to prevent instantiation from outside
	LoginManager() : m_database(&SqliteDataBase::getInstance())
	{
	}

	// Private copy constructor to prevent cloning
	LoginManager(const LoginManager&);
};
