#pragma once
#include "SqliteDataBase.h"
#include <vector>
#include "LoggedUser.h"

class LoginManager
{
public:
	void singup(std::string username, std::string password, std::string email);
	void login(std::string username, std::string password);
	void logout(std::string username);
private:
	std::vector<LoggedUser> m_loggedUsers;
	IDatabase* m_database;
};

