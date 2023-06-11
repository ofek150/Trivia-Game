#pragma once

enum ResponseCodes
{
	ErrorResponseCode = 0,
	LoginResponseCode = 1,
	SignupResponseCode = 2,
	LogoutResponseCode = 3,
	JoinRoomResponseCode = 4,
	GetRoomsResponseCode = 5,
	GetPlayersInRoomResponseCode = 6,
	CreateRoomResponseCode = 7,
	GetHighScoreResponseCode = 8,
	GetPersonalStatsResponseCode = 9,
	CloseRoomResponseCode = 10,
	StartGameResponseCode = 11,
	GetRoomStateResponseCode = 12,
	LeaveRoomResponseCode = 13,
	GetGameResultsResponseCode = 14,
	SubmitAnswerResponseCode = 15,
	GetQuestionResponseCode = 16,
	LeaveGameResponseCode = 17
};