#pragma once
#include <string>
#include <vector>
#include "SqliteDataBase.h"

class Question
{
public:
	Question(std::string question, std::vector<std::string> possibleAnswers);
	std::string getQuestion() const;
	std::vector<std::string> getPossibleAnswers() const;
	int getCorrectAnswerId() const;
private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
};

