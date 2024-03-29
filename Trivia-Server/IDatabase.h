#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "GameData.h"

class IDatabase
{
public:
	virtual bool open() = 0;
	virtual void close() = 0;
	virtual void clear() = 0;
	virtual bool doesUserExist(const std::string& username) = 0;
	virtual bool isPasswordValid(const std::string& username, const std::string& password) = 0;
	virtual void insertUserIntoDB(const std::string& username, const std::string& password,
	                              const std::string& email) = 0;
	virtual int getNumOfPlayerGames(std::string username) = 0;
	virtual int getNumOfTotalAnswers(std::string username) = 0;
	virtual int getNumOfCorrectAnswers(std::string username) = 0;
	virtual double getPlayerAverageAnswerTime(std::string username) = 0;
	virtual std::vector<std::string> getTopUserGrades() const = 0;
	virtual std::vector<std::string> getQuestions(int amount, std::string category) const = 0;
	virtual std::vector<std::string> getPossibleAnswers(const std::string& title) const = 0;
	virtual int getAnswerIdByTitle(const std::string& title) const = 0;
	virtual void submitGameStats(std::string username, const GameData& data) const = 0;
};
