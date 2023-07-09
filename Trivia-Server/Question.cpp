#include "Question.h"

Question::Question(std::string question, std::vector<std::string> possibleAnswers, int correctAnswerId) :
	m_question(question), m_correctAnswerId(correctAnswerId)
{
	for (int i = 0; i < possibleAnswers.size(); i++)
	{
		m_possibleAnswers.emplace_back(possibleAnswers[i]);
	}
}


std::string Question::getQuestion() const
{
	return m_question;
}

std::vector<std::string> Question::getPossibleAnswers() const
{
	return m_possibleAnswers;
}

int Question::getCorrectAnswerId() const
{
	return m_correctAnswerId;
}
