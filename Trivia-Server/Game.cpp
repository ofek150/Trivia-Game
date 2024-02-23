#include "Game.h"

Game::Game(const std::vector<Question>& questions, const std::vector<LoggedUser>& players, int gameId,
           std::string category) : m_questions(questions), m_gameId(gameId), m_category(category)
{
	try
	{
		m_total_questions = m_questions.size();
		m_currentQuestion = m_questions.at(0);
		m_question_counter = 1;
		if (!m_questions.empty())
		{
			m_questions.erase(m_questions.begin());
		}
	}
	catch (const std::out_of_range& e)
	{
		std::cerr << "Caught an out_of_range exception: " << e.what() << '\n';
	}

	for (const auto& player : players)
	{
		GameData gameData;
		gameData.avgAnswerTime = 0;
		gameData.correctAnswerCount = 0;
		gameData.wrongAnswerCount = 0;
		m_players[player] = gameData;
	}
}


Question Game::getCurrentQuestion()
{
	return m_currentQuestion;
}

void Game::submitAnswer(const LoggedUser& user, int answerId)
{
	if (answerId == m_currentQuestion.getCorrectAnswerId())
	{
		m_players[user].correctAnswerCount++;
	}
	else
	{
		m_players[user].wrongAnswerCount++;
	}
	//need to add avg time
	m_players[user].avgAnswerTime = 0;
	if (m_submited_players_counter == m_players.size())
	{
		if (m_question_counter != m_total_questions)
		{
			if (!m_questions.empty())
			{
				m_currentQuestion = m_questions.at(0);
				m_question_counter += 1;
				if (!m_questions.empty())
				{
					m_questions.erase(m_questions.begin());
				}
			}
			return;
		}
		for (const auto& pair : m_players)
		{
			SqliteDataBase::getInstance().submitGameStats(pair.first.getUsername(), pair.second);
		}
		std::vector<std::string> emptyVector;
		m_currentQuestion = Question("", emptyVector, 0);
	}
}

int Game::getGameId() const
{
	return m_gameId;
}

void Game::removePlayer(const LoggedUser& user)
{
	std::lock_guard<std::mutex> players_lock(players_mutex);
	auto it = std::find_if(m_players.begin(), m_players.end(),
		[&](const std::pair<LoggedUser, GameData>& u) { return u.first.getUsername() == user.getUsername(); });
	if (it != m_players.end()) it->second.isActive = false;
}


bool Game::areAllPlayersInactive() const
{
	for (const auto& pair : m_players)
	{
		const GameData& gameData = pair.second;
		if (gameData.isActive)
		{
			return false;
		}
	}
	return true;
}

std::vector<PlayerResults> Game::getPlayersResults()
{
	std::vector<PlayerResults> results;
	for (const auto& player : m_players)
	{
		PlayerResults result;
		result.username = player.first.getUsername();
		result.correctAnswerCount = player.second.correctAnswerCount;
		result.wrongAnswerCount = player.second.wrongAnswerCount;
		result.averageAnswerTime = player.second.avgAnswerTime;
		results.emplace_back(result);
	}
	return results;
}
