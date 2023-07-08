#pragma once
#include "IDatabase.h"
#include <vector>
#include "Game.h"
#include "Room.h"
#include "SqliteDataBase.h"
#include <string>

class GameManager
{
public:
	void operator=(const GameManager&) = delete;

	// Public static function to get the singleton instance
	static GameManager& getInstance() {
		static GameManager instance;
		return instance;
	}
	Game& createGame(const Room& room);
	void deleteGame(const int gameId);
	Game& getGameById(const int gameId);

private:
	IDatabase* m_database;
	std::vector<Game> m_games;

	// Private constructor to prevent instantiation from outside
	GameManager() {}

	// Private copy constructor to prevent cloning
	GameManager(const GameManager&);
};

