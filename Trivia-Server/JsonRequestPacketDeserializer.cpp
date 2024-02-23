#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const std::vector<unsigned char>& buffer)
{
	nlohmann::json json_data = parseJsonData(buffer);

	LoginRequest request;
	if (json_data.contains("username") && json_data.contains("password"))
	{
		request.username = json_data["username"].get<std::string>();
		request.password = json_data["password"].get<std::string>();
	}

	return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const std::vector<unsigned char>& buffer)
{
	nlohmann::json json_data = parseJsonData(buffer);

	SignupRequest request;
	if (json_data.contains("username") && json_data.contains("password") && json_data.contains("email"))
	{
		request.username = json_data["username"].get<std::string>();
		request.password = json_data["password"].get<std::string>();
		request.email = json_data["email"].get<std::string>();
	}

	return request;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(
	const std::vector<unsigned char>& buffer)
{
	nlohmann::json json_data = parseJsonData(buffer);

	GetPlayersInRoomRequest request;
	if (json_data.contains("roomId"))
	{
		request.roomId = json_data["roomId"].get<unsigned int>();
	}

	return request;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const std::vector<unsigned char>& buffer)
{
	nlohmann::json json_data = parseJsonData(buffer);

	JoinRoomRequest request;
	if (json_data.contains("roomId"))
	{
		request.roomId = json_data["roomId"].get<unsigned int>();
	}

	return request;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const std::vector<unsigned char>& buffer)
{
	nlohmann::json json_data = parseJsonData(buffer);

	CreateRoomRequest request;
	if (json_data.contains("roomName") && json_data.contains("maxUsers") && json_data.contains("questionCount") &&
		json_data.contains("answerTimeout"))
	{
		request.roomName = json_data["roomName"].get<std::string>();
		request.maxUsers = json_data["maxUsers"].get<unsigned int>();
		request.questionCount = json_data["questionCount"].get<unsigned int>();
		request.answerTimeout = json_data["answerTimeout"].get<unsigned int>();
		request.category = json_data["category"].get<std::string>();
	}

	return request;
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(
	const std::vector<unsigned char>& buffer)
{
	nlohmann::json json_data = parseJsonData(buffer);
	SubmitAnswerRequest request;
	if (json_data.contains("answerId")) request.answerId = json_data["answerId"].get<unsigned int>();
	return request;
}

std::string JsonRequestPacketDeserializer::deserializeErrorResponse(const std::vector<unsigned char>& buffer)
{
	nlohmann::json json_data = parseJsonData(buffer);

	CreateRoomRequest request;
	if (json_data.contains("message"))
	{
		return json_data["message"];
	}
	return "";
}

nlohmann::json JsonRequestPacketDeserializer::parseJsonData(const std::vector<unsigned char>& buffer)
{
	std::string buffer_str(buffer.begin(), buffer.end());
	std::string json_str = buffer_str.substr(buffer_str.find('{')); // Get only the JSON part in the buffer
	return nlohmann::json::parse(json_str);
}
