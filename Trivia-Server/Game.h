#pragma once
#include "GameData.h"
#include <vector>
#include <map>
#include "LoggedUser.h"
#include <mutex>
#include "Responses.h"
#include "Requests.h"

class Game
{
public:
	Game(const std::vector<Question>& questions, const std::vector<LoggedUser>& players, int gameId);
	Question getCurrentQuestion();
	void submitAnswer(const LoggedUser& user, int answerId);
	int getGameId() const;
	void removePlayer(const LoggedUser& user);
	bool areAllPlayersInactive() const;
	std::vector<PlayerResults> getPlayersResults();
private:
	Question m_currentQuestion;
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	int m_gameId;
	int m_submited_players_counter;
	int m_total_questions;
	int m_question_counter;
	std::mutex players_mutex;
};

