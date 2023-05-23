#include "StatisticsManager.h"

std::vector<std::string> StatisticsManager::getHighScore() const
{   
    std::vector<std::string> user_stats;
    SqliteDataBase* x;
    x = (SqliteDataBase*)m_database;
    return x->getTopUserGrades();
}

std::vector<std::string> StatisticsManager::getUserStatistics(const std::string& username) const
{
    std::vector<std::string> user_stats;
    SqliteDataBase* x;
    x = (SqliteDataBase*)m_database;
    int numOfPlayerGames = x->getNumOfPlayerGames(username);
    user_stats.emplace_back("User played: " + std::to_string(numOfPlayerGames));
    int usersTotalAnswers = x->getNumOfTotalAnswers(username);
    user_stats.emplace_back("User's total answers: " + std::to_string(usersTotalAnswers));
    int usersCorrectAnswers = x->getNumOfCorrectAnswers(username);
    user_stats.emplace_back("User's Correct answers: " + std::to_string(usersCorrectAnswers));
    double usersAvgTime = x->getPlayerAverageAnswerTime(username);
    user_stats.emplace_back("User's average time: " + std::to_string(usersAvgTime));
    return user_stats;
}
