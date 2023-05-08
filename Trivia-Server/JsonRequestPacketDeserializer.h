#pragma once

#include "LoginRequest.h"
#include "SignupRequest.h"
#include "json.hpp"
#include <ctime>
#include <iostream>
#include <string>
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
    static LoginRequest deserializeLoginRequest(const std::vector<unsigned char>& buffer);
    static SignupRequest deserializeSignupRequest(const std::vector<unsigned char>& buffer);



private:

    // Private constructor to prevent instantiation from outside
    JsonRequestPacketDeserializer() {}

    // Private copy constructor to prevent cloning
    JsonRequestPacketDeserializer(const JsonRequestPacketDeserializer&);

};


