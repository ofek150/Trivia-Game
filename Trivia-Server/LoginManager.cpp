#include "LoginManager.h"

void LoginManager::signup(std::string username, std::string password, std::string email)
{
	m_database->insertUserIntoDB(username, password, email);
}

void LoginManager::login(std::string username, std::string password)
{
	if (!this->m_database->doesUserExist(username) || !this->m_database->isPasswordValid(username, password))
		return;
	LoggedUser newUser(username);
	this->m_loggedUsers.emplace_back(newUser);
}

void LoginManager::logout(std::string username)
{
	auto it = std::remove_if(m_loggedUsers.begin(), m_loggedUsers.end(), 
		[username](LoggedUser& user) {return user.getUsername() == username;});
	if (it != m_loggedUsers.end()) 
		m_loggedUsers.erase(it, m_loggedUsers.end());
	
}
