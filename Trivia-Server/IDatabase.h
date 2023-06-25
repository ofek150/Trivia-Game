#include <string>
#include <iostream>

class IDatabase
{
public:
	
	virtual bool open() = 0;
	virtual void close() = 0;
	virtual void clear() = 0;
	virtual bool doesUserExist(const std::string& username) = 0;
	virtual bool isPasswordValid(const std::string& username, const std::string& password) = 0;
	virtual void insertUserIntoDB(const std::string& username, const std::string& password, const std::string& email) = 0;
	virtual int getNumOfPlayerGames(const std::string username) = 0;
	virtual int getNumOfTotalAnswers(const std::string username) = 0;
	virtual int getNumOfCorrectAnswers(const std::string username) = 0;
	virtual double getPlayerAverageAnswerTime(const std::string username) = 0;
	virtual std::vector<std::string> getTopUserGrades() const = 0;
	virtual std::vector<std::string> getQuestions(const int amount) const = 0;
	virtual std::vector<std::string> getPossibleAnswers(const std::string& title) const = 0;
	virtual int getAnswerIdByTitle(const std::string& title) const = 0;
	virtual void submitGameStats(const unsigned int gameId, const GameData& data) const = 0;
};

