#pragma once
#include "GameData.h"
#include <vector>
#include <map>
#include "LoggedUser.h"

class Game
{
public:
	Question getQuestionForUser(const LoggedUser user);
	void submitAnswer(const LoggedUser user, int answerId);
	void removePlayer(LoggedUser user);
private:
	Question currentQuestion;
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	int m_gameId;
};

