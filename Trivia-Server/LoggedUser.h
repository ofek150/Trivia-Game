#pragma once
#include <string>
class LoggedUser
{
public:
	LoggedUser(std::string username);
	LoggedUser() = delete;
	const std::string getUsername() const;
private:
	std::string m_username;
};

