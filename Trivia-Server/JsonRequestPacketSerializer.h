#pragma once

#include "ErrorResponse.h"
#include "LoginResponse.h"
#include "SignupResponse.h"
#include "ResponseCodes.h"
#include "json.hpp"

#include <vector>


class JsonRequestPacketSerializer {
public:

    void operator=(const JsonRequestPacketSerializer&) = delete;

    // Public static function to get the singleton instance
    static JsonRequestPacketSerializer& getInstance() {
        static JsonRequestPacketSerializer instance;
        return instance;
    }

    // Public member functions for serializing responses
    static const std::vector<unsigned char> serializeResponse(const ErrorResponse& response);
    static const std::vector<unsigned char> serializeResponse(const LoginResponse& response);
    static const std::vector<unsigned char> serializeResponse(const SignupResponse& response);

    
private:
    static const std::vector<unsigned char> constructPacket(int response_code, std::string json_dump); // Constructs the packet from
    

    // Private constructor to prevent instantiation from outside
    JsonRequestPacketSerializer() {}

    // Private copy constructor to prevent cloning
    JsonRequestPacketSerializer(const JsonRequestPacketSerializer&);
    
};


