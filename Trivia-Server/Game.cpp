#include "Game.h"

Game::Game(const std::vector<Question>& questions, const std::vector<LoggedUser>& players, int gameId) : m_questions(questions), m_gameId(gameId)
{
    try {
        m_total_questions = m_questions.size();
        m_currentQuestion = m_questions.at(0);
        m_question_counter = 1;
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
    if (m_submited_players_counter == m_players.size()) {
        if (m_question_counter != m_total_questions)
        {
            if (!m_questions.empty()) {
                m_currentQuestion = m_questions.at(0);
                m_question_counter += 1;
                if (!m_questions.empty()) {
                    m_questions.erase(m_questions.begin());
                }
            }
            return;
        }
        std::vector<std::string> emptyVector;
        m_currentQuestion = Question("", emptyVector, 0);
        
    }
}

int Game::getGameId() const
{
    return m_gameId;
}

void Game::removePlayer(LoggedUser& user)
{
    std::lock_guard<std::mutex> players_lock(players_mutex);
    auto it = std::find_if(m_players.begin(), m_players.end(),
        [&](const LoggedUser& u) { return u.getUsername() == user.getUsername(); });

    if (it != m_players.end()) m_users.erase(it);
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