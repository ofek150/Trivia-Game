#include "LoginManager.h"

void LoginManager::signup(std::string username, std::string password, std::string email)
{
	if (username.empty()) throw std::exception("Username can't be empty!");
	if (email.empty()) throw std::exception("Email can't be empty!");
	if (password.empty()) throw std::exception("Password can't be empty!");

	if (this->m_database->doesUserExist(username)) throw std::exception("A user with that username already exists!");;
	m_database->insertUserIntoDB(username, password, email);
}

void LoginManager::login(std::string username, std::string password)
{
	if (username.empty()) throw std::exception("Username can't be empty!");
	if (password.empty()) throw std::exception("Password can't be empty!");

	if(isUserInLoggedUsers(username)) throw std::exception("That user is already logged in!");
	if (!this->m_database->doesUserExist(username)) throw std::exception("Username doesn't exist!");
	if (!this->m_database->isPasswordValid(username, password)) throw std::exception("Invalid password!");

	std::lock_guard<std::mutex> users_lock(loggedUsers_mutex);
	LoggedUser newUser(username);
	this->m_loggedUsers.emplace_back(newUser);
}

void LoginManager::logout(std::string username)
{
	std::lock_guard<std::mutex> users_lock(loggedUsers_mutex);
	auto it = std::remove_if(m_loggedUsers.begin(), m_loggedUsers.end(), 
		[username](LoggedUser& user) {return user.getUsername() == username;});

	if (it != m_loggedUsers.end()) 
		m_loggedUsers.erase(it, m_loggedUsers.end());
	
}

bool LoginManager::isUserInLoggedUsers(const std::string& username)
{
	for (const LoggedUser& user : m_loggedUsers) {
		if (user.getUsername() == username) {
			return true;
		}
	}
	return false;
}
