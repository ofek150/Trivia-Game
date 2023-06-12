#include "Question.h"

Question::Question(std::string question, std::vector<std::string> possibleAnswers) : m_question(question)
{
    for (int i = 0; i < possibleAnswers.size(); i++) {
        m_possibleAnswers.emplace_back(possibleAnswers[i]);
    }
}

std::string Question::getQuestion() const
{
    
    return this->m_question;
}

std::vector<std::string> Question::getPossibleAnswers() const
{
    return this->m_possibleAnswers;
}

int Question::getCorrectAnswerId() const
{
    return 0;//need to fix
}
