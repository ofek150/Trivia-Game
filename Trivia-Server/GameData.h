#pragma once
#include "Question.h"

struct GameData {
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	double avgAnswerTime;
	bool isActive;
};