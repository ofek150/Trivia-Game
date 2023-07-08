#pragma once
#include <string>
#include <vector>
#include "RoomData.h"
#include "Requests.h"

struct ErrorResponse {
    std::string errorMessage;
};

struct SignupResponse {
    unsigned int status;
};

struct LoginResponse {
    unsigned int status;
};

struct LogoutResponse {
    unsigned int status;
};

struct GetRoomsResponse {
    unsigned int status;
    std::vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse {
    std::vector<std::string> players;
};

struct GetHighScoreRoomResponse {
    unsigned int status;
    std::vector<std::string> statistics;
};

struct GetPersonalStatsResponse {
    unsigned int status;
    std::vector<std::string> statistics;
};

struct JoinRoomResponse {
    unsigned int status;
};

struct CreateRoomResponse {
    unsigned int status;
    unsigned int roomId;
};

struct CloseRoomResponse {
    unsigned int status;
};

struct StartGameResponse {
    unsigned int status;
};

struct GetRoomStateResponse {
    unsigned int status;
    bool hasGameBegun;
    std::vector<std::string> players;
    unsigned int questionCount;
    unsigned int answerTimeOut;
};

struct LeaveRoomResponse {
    unsigned int status;
};

struct GetGameResultsResponse {
    unsigned int status;
    std::vector<PlayerResults> results;
};

struct SubmitAnswerResponse {
    unsigned int status;
    unsigned int correctsAnswerId;
};

struct GetQuestionResponse {
    unsigned int status;
    std::string question;
    std::vector<std::string> answers;
};

struct LeaveGameResponse {
    unsigned int status;
};