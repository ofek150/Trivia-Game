#include "JsonRequestPacketSerializer.h"

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const ErrorResponse& response)
{
    nlohmann::json json_data = { {"message", response.errorMessage} };
    return constructPacket(ResponseCodes::ErrorResponseCode, json_data.dump());
}

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const LoginResponse& response)
{
    nlohmann::json json_data = { {"status", response.status} };
    return constructPacket(ResponseCodes::LoginResponseCode, json_data.dump());
}

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const SignupResponse& response)
{
    nlohmann::json json_data = { {"status", response.status} };
    return constructPacket(ResponseCodes::SignupResponseCode, json_data.dump());
}

const std::vector<unsigned char> JsonRequestPacketSerializer::constructPacket(int response_code, std::string json_dump) const
{
    std::vector<unsigned char> buffer;

    // Converting the response code to a 1 byte int
    uint8_t response_code_1byte = static_cast<uint8_t>(response_code);
    buffer.push_back(response_code_1byte);

    // Add the JSON data length to the buffer
    unsigned int json_length = json_dump.length();
    buffer.insert(buffer.end(), reinterpret_cast<const unsigned char*>(&json_length), reinterpret_cast<const unsigned char*>(&json_length) + sizeof(unsigned int));

    // Add the JSON data to the buffer
    buffer.insert(buffer.end(), json_dump.begin(), json_dump.end());

    return buffer;
}
