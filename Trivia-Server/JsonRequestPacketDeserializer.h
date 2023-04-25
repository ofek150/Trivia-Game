#pragma once

#include "LoginRequest.h"
#include "SignupRequest.h"
#include "json.hpp"
#include <ctime>
#include <iostream>

#include <vector>


class JsonRequestPacketDeserializer {
public:

    void operator=(const JsonRequestPacketDeserializer&) = delete;

    // Public static function to get the singleton instance
    static JsonRequestPacketDeserializer& getInstance() {
        static JsonRequestPacketDeserializer instance;
        return instance;
    }

    // Public member functions for serializing responses
    LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer) const;
    SignupRequest deserializeSignupRequest(std::vector<unsigned char> buffer) const;


private:
    // Private constructor to prevent instantiation from outside
    JsonRequestPacketDeserializer() {}

    // Private copy constructor to prevent cloning
    JsonRequestPacketDeserializer(const JsonRequestPacketDeserializer&);

};


