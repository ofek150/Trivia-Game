#pragma once

#include "ErrorResponse.h"
#include "LoginResponse.h"
#include "SignupResponse.h"

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
    std::vector<unsigned char> serializeResponse(const ErrorResponse& response) const;
    std::vector<unsigned char> serializeResponse(const LoginResponse& response) const;
    std::vector<unsigned char> serializeResponse(const SignupResponse& response) const;

    
private:
    // Private constructor to prevent instantiation from outside
    JsonRequestPacketSerializer() {}

    // Private copy constructor to prevent cloning
    JsonRequestPacketSerializer(const JsonRequestPacketSerializer&);
    
};


