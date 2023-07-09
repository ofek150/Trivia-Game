#pragma once
#include "IDatabase.h"
#include "Game.h"
#include "Room.h"
#include <vector>

class Room;

class GameManager
{
public:
    void operator=(const GameManager&) = delete;

    // Public static function to get the singleton instance
    static GameManager& getInstance()
    {
        static GameManager instance;
        return instance;
    }

    Game& createGame(const Room& room);
    void deleteGame(int gameId);
    Game& getGameById(unsigned int gameId);

private:
    IDatabase* m_database;
    std::vector<Game> m_games;

    // Private constructor to prevent instantiation from outside
    GameManager() {}

    // Private copy constructor to prevent cloning
    GameManager(const GameManager&);
};
