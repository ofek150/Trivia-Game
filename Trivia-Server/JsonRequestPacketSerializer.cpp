#include "JsonRequestPacketSerializer.h"
#include <iostream>

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const ErrorResponse& response)
{
	nlohmann::json json_data = {{"message", response.errorMessage}};
	return constructPacket(ErrorResponseCode, json_data.dump());
}

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const LoginResponse& response)
{
	nlohmann::json json_data = {{"status", response.status}};
	return constructPacket(LoginResponseCode, json_data.dump());
}

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const SignupResponse& response)
{
	nlohmann::json json_data = {{"status", response.status}};
	return constructPacket(SignupResponseCode, json_data.dump());
}

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const LogoutResponse& response)
{
	nlohmann::json json_data = {{"status", response.status}};
	return constructPacket(LogoutResponseCode, json_data.dump());
}

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const GetRoomsResponse& response)
{
	nlohmann::json json_data;

	json_data["status"] = response.status;
	json_data["Rooms"] = {}; // Initialize "Rooms" as an empty array
	int count = 0;

	for (const auto& room : response.rooms)
	{
		nlohmann::json room_data;
		room_data["roomId"] = room.id;
		room_data["isActive"] = room.isActive;
		room_data["timePerQuestion"] = room.timePerQuestion;
		room_data["numOfQuestionsInGame"] = room.numOfQuestionsInGame;
		room_data["maxPlayers"] = room.maxPlayers;
		room_data["name"] = room.name;
		room_data["category"] = room.category;
		json_data["Rooms"][count] = room_data;
		count++;
	}

	std::cout << json_data.dump() << std::endl;
	return constructPacket(GetRoomsResponseCode, json_data.dump());
}


const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(
	const GetPlayersInRoomResponse& response)
{
	nlohmann::json json_data;

	// Serialize the players as a single string
	std::string playersString;
	for (const auto& player : response.players)
	{
		if (!playersString.empty())
			playersString += ", ";
		playersString += player;
	}
	json_data["PlayersInRoom"] = playersString;

	return constructPacket(GetPlayersInRoomResponseCode, json_data.dump());
}


const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const JoinRoomResponse& response)
{
	nlohmann::json json_data = {{"status", response.status}};
	return constructPacket(JoinRoomResponseCode, json_data.dump());
}

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const CreateRoomResponse& response)
{
	nlohmann::json json_data;
	json_data["status"] = response.status;
	json_data["roomId"] = response.roomId;
	return constructPacket(CreateRoomResponseCode, json_data.dump());
}

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(
	const GetHighScoreRoomResponse& response)
{
	nlohmann::json json_data;
	json_data["status"] = response.status;
	json_data["HighScores"] = response.statistics;

	return constructPacket(GetHighScoreResponseCode, json_data.dump());
}

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(
	const GetPersonalStatsResponse& response)
{
	nlohmann::json json_data;
	json_data["status"] = response.status;
	json_data["UserStatistics"] = response.statistics;

	return constructPacket(GetPersonalStatsResponseCode, json_data.dump());
}

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const CloseRoomResponse& response)
{
	nlohmann::json json_data = {{"status", response.status}};
	return constructPacket(CloseRoomResponseCode, json_data.dump());
}

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const StartGameResponse& response)
{
	nlohmann::json json_data = {{"status", response.status}};
	return constructPacket(StartGameResponseCode, json_data.dump());
}

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const GetRoomStateResponse& response)
{
	nlohmann::json json_data;
	json_data["status"] = response.status;
	json_data["hasGameBegun"] = response.hasGameBegun;
	json_data["players"] = response.players;
	json_data["questionCount"] = response.questionCount;
	json_data["answerTimeOut"] = response.answerTimeOut;

	return constructPacket(GetRoomStateResponseCode, json_data.dump());
}

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const LeaveRoomResponse& response)
{
	nlohmann::json json_data = {{"status", response.status}};
	return constructPacket(LeaveRoomResponseCode, json_data.dump());
}

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const GetGameResultsResponse& response)
{
	nlohmann::json json_data;
	json_data["status"] = response.status;
	std::string serializedResults = playerResultVectToStr(response.results);
	json_data["results"] = serializedResults;
	return constructPacket(GetGameResultsResponseCode, json_data.dump());
}


const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const SubmitAnswerResponse& response)
{
	nlohmann::json json_data;
	json_data["status"] = response.status;
	json_data["correctsAnswerId"] = response.correctsAnswerId;
	return constructPacket(SubmitAnswerResponseCode, json_data.dump());
}

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const GetQuestionResponse& response)
{
	nlohmann::json json_data;
	json_data["status"] = response.status;
	json_data["question"] = response.question;
	json_data["answers"] = response.answers;
	return constructPacket(GetQuestionResponseCode, json_data.dump());
}

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const LeaveGameResponse& response)
{
	nlohmann::json json_data = {{"status", response.status}};
	return constructPacket(LeaveRoomResponseCode, json_data.dump());
}

const std::vector<unsigned char> JsonRequestPacketSerializer::constructPacket(int response_code, std::string json_dump)
{
	std::vector<unsigned char> buffer;

	// Converting the response code to a 1 byte int
	uint8_t response_code_1byte = static_cast<uint8_t>(response_code);
	buffer.push_back(response_code_1byte);

	// Add the JSON data length to the buffer
	unsigned int json_length = json_dump.length();

	buffer.insert(buffer.end(), reinterpret_cast<const unsigned char*>(&json_length),
	              reinterpret_cast<const unsigned char*>(&json_length) + sizeof(unsigned int));

	// Add the JSON data to the buffer
	buffer.insert(buffer.end(), json_dump.begin(), json_dump.end());

	return buffer;
}

const std::string JsonRequestPacketSerializer::playerResultVectToStr(const std::vector<PlayerResults>& values)
{
	std::ostringstream oss;
	if (!values.empty())
	{
		auto it = values.begin();
		oss << it->averageAnswerTime << "," << it->correctAnswerCount << "," << it->wrongAnswerCount;
		for (++it; it != values.end(); ++it)
		{
			oss << "|" << it->averageAnswerTime << "," << it->correctAnswerCount << "," << it->wrongAnswerCount;
		}
	}
	return oss.str();
}
