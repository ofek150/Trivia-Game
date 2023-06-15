#include "Game.h"

Game::Game(const std::vector<Question>& questions, const std::vector<LoggedUser>& players, int gameId) : m_questions(questions), m_gameId(gameId)
{
    try {
        m_currentQuestion = m_questions.at(0);
        if (!m_questions.empty()) {
            m_questions.erase(m_questions.begin());
        }
    }
    catch (const std::out_of_range& e) {
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


Question Game::getQuestionForUser(const LoggedUser& user)
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
}

int Game::getGameId() const
{
    return m_gameId;
}

void Game::removePlayer(LoggedUser& user)
{
    for (auto it = m_players.begin(); it != m_players.end(); )
    {
        if (it->first.getUsername() == user.getUsername())
        {
            it->second.isActive = false;
            break;
        }
        else
        {
            ++it;
        }
    }
}

bool Game::areAllPlayersInactive() const {
    for (const auto& pair : m_players) {
        const GameData& gameData = pair.second;
        if (gameData.isActive) {
            return false;
        }
    }
    return true;
}