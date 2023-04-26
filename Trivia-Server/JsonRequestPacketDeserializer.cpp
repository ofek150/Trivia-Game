#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const std::string& buffer)
{
    std::string json_str = buffer.substr(buffer.find('{')); // Get only the JSON part in the buffer
    nlohmann::json json_data = nlohmann::json::parse(json_str);

    LoginRequest login_request;
    if (json_data.contains("username") && json_data.contains("password")) {
        login_request.username = json_data["username"].get<std::string>();
        login_request.password = json_data["password"].get<std::string>();
    }

    return login_request;

}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const std::string& buffer)
{
    std::string json_str = buffer.substr(buffer.find('{')); // Get only the JSON part in the buffer
    nlohmann::json json_data = nlohmann::json::parse(json_str);

    SignupRequest signup_request;
    if (json_data.contains("username") && json_data.contains("password") && json_data.contains("email")) {
        signup_request.username = json_data["username"].get<std::string>();
        signup_request.password = json_data["password"].get<std::string>();
        signup_request.email = json_data["email"].get<std::string>();;
    }

    return signup_request;
}
