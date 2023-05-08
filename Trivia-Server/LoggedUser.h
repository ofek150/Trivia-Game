#pragma once
#include <string>
class LoggedUser
{
public:
	LoggedUser(std::string username);
	const std::string getUsername() const;
private:
	std::string m_username;
};

