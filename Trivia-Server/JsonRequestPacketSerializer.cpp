#include "JsonRequestPacketSerializer.h"

std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const ErrorResponse& response) const
{
    std::vector<unsigned char> buffer;

    // Serialize the error message
    std::string errorMessage = response.errorMessage;
    buffer.insert(buffer.end(), errorMessage.c_str(), errorMessage.c_str() + errorMessage.length());

    return buffer;
}

std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const LoginResponse& response) const
{
    std::vector<unsigned char> buffer;

    // Serialize the status
    unsigned int status = response.status;
    buffer.insert(buffer.end(), reinterpret_cast<const unsigned char*>(&status), reinterpret_cast<const unsigned char*>(&status) + sizeof(unsigned int));

    return buffer;
}

std::vector<unsigned char> JsonRequestPacketSerializer::serializeResponse(const SignupResponse& response) const
{
    std::vector<unsigned char> buffer;

    // Serialize the status
    unsigned int status = response.status;
    buffer.insert(buffer.end(), reinterpret_cast<const unsigned char*>(&status), reinterpret_cast<const unsigned char*>(&status) + sizeof(unsigned int));

    return buffer;
}
