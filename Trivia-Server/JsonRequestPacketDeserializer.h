#pragma once

#include "Requests.h"
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
    static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(const std::vector<unsigned char>& buffer);
    static JoinRoomRequest deserializeJoinRoomRequest(const std::vector<unsigned char>& buffer);
    static CreateRoomRequest deserializeCreateRoomRequest(const std::vector<unsigned char>& buffer);

    static std::string deserializeErrorResponse(const std::vector<unsigned char>& buffer);


private:

    static nlohmann::json parseJsonData(const std::vector<unsigned char>& buffer);

    // Private constructor to prevent instantiation from outside
    JsonRequestPacketDeserializer() {}

    // Private copy constructor to prevent cloning
    JsonRequestPacketDeserializer(const JsonRequestPacketDeserializer&);

};


