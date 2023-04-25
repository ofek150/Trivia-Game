#include "JsonRequestPacketSerializer.h"

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const ErrorResponse& response) const
{
    std::vector<unsigned char> buffer;

    // Serialize the error message
    
    unsigned int response_code = ResponseCodes::ErrorResponseCode;
    std::string errorMessage = response.errorMessage;

    nlohmann::json json_data;
    json_data["message"] = response.errorMessage;
    std::string json_dump = json_data.dump();

    // Add the response code to the buffer
    buffer.insert(buffer.end(), reinterpret_cast<const unsigned char*>(&response_code), reinterpret_cast<const unsigned char*>(&response_code) + sizeof(unsigned int));
    
    // Add the JSON data length to the buffer
    unsigned int json_length = json_dump.length();
    buffer.insert(buffer.end(), reinterpret_cast<const unsigned char*>(&json_length), reinterpret_cast<const unsigned char*>(&json_length) + sizeof(unsigned int));

    // Add the JSON data to the buffer
    buffer.insert(buffer.end(), json_dump.begin(), json_dump.end());


    return buffer;
}

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const LoginResponse& response) const
{
    std::vector<unsigned char> buffer;

    // Serialize the status
    unsigned int status = response.status;
    buffer.insert(buffer.end(), reinterpret_cast<const unsigned char*>(&status), reinterpret_cast<const unsigned char*>(&status) + sizeof(unsigned int));

    return buffer;
}

const std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const SignupResponse& response) const
{
    std::vector<unsigned char> buffer;

    // Serialize the status
    unsigned int status = response.status;
    buffer.insert(buffer.end(), reinterpret_cast<const unsigned char*>(&status), reinterpret_cast<const unsigned char*>(&status) + sizeof(unsigned int));

    return buffer;
}
