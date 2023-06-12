#pragma once
#include "Question.h"
struct GameData {
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	double avgAnswerTime;
};