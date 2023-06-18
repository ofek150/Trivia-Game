#include "GameManager.h"

Game& GameManager::createGame(const Room& room)
{
    std::vector<std::string> questionsTitle = m_database->getQuestions(room.getRoomData().numOfQuestionsInGame);
    std::vector<Question> questions;
    for (int i = 0; i < questionsTitle.size(); i++) {
        Question q(questionsTitle[i], m_database->getPossibleAnswers(questionsTitle[i]), m_database->getAnswerIdByTitle(questionsTitle[i]));
        questions.emplace_back(q);
    }
    std::vector<LoggedUser> newGamePlayers;
    for (const auto& player : room.getAllUsers()) {
        newGamePlayers.emplace_back(player);
    }
    Game newGame(questions, newGamePlayers, room.getRoomData().id);
    m_games.emplace_back(newGame);
    return getGameById(room.getRoomData().id);//do it in room 
}

void GameManager::deleteGame(const int gameId) {
    auto it = std::find_if(m_games.begin(), m_games.end(), [gameId](const Game& game) {
        return game.getGameId() == gameId;
        });
    if (it != m_games.end()) {
        const Game& game = *it;
        if (game.areAllPlayersInactive()) {
            m_games.erase(it);
        }
    }
}

Game& GameManager::getGameById(const int gameId)
{
    for (auto& game : m_games) 
        if (game.getGameId() == gameId) 
            return game;
    throw std::exception(("Game not found with ID: " + std::to_string(gameId)).c_str());
}
