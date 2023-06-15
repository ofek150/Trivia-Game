#pragma once
#include "GameData.h"
#include <vector>
#include <map>
#include "LoggedUser.h"
#include <mutex>
class Game
{
public:
	Game(const std::vector<Question>& questions, const std::vector<LoggedUser>& players, int gameId);
	Question getQuestionForUser(const LoggedUser& user);
	void submitAnswer(const LoggedUser& user, int answerId);
	int getGameId() const;
	void removePlayer(LoggedUser& user);
	bool areAllPlayersInactive() const;
private:
	Question m_currentQuestion;
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	int m_gameId;
	int submited_players_counter;
	std::mutex user_mutex;
};

