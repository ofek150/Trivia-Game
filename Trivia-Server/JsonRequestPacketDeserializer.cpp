#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const std::string& buffer)
{
    std::string data = buffer.substr(buffer.find('{')); // Get only the json part in the buffer

    nlohmann::json json_Data = nlohmann::json::parse(data); // parse to json
    //Extracting the json data and parsing it.
    int json_size = buffer.size() - sizeof(int) - sizeof(time_t);
    std::string json_str(buffer[sizeof(int) + sizeof(std::time_t)], json_size);
    nlohmann::json json_data = nlohmann::json::parse(json_str);


    LoginRequest login_request;
    login_request.username = json_data["username"].get<std::string>();
    login_request.password = json_data["password"].get<std::string>();

    return login_request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const std::string& buffer)
{
    //Extracting message code
    int message_code = static_cast<int>(buffer[0]);

    //Extracting the time of arrival
    time_t timestamp = *reinterpret_cast<time_t*>(&buffer[sizeof(int)]);

    //Extracting the json data and parsing it.
    int json_size = buffer.size() - sizeof(int) - sizeof(time_t);
    std::string json_str(buffer[sizeof(int) + sizeof(std::time_t)], json_size);
    nlohmann::json json_data = nlohmann::json::parse(json_str);


    SignupRequest signup_request;
    signup_request.username = json_data["username"].get<std::string>();
    signup_request.password = json_data["password"].get<std::string>();
    signup_request.email = json_data["email"].get<std::string>();

    return signup_request;
}
