#pragma once
#include <vector>
#include <string>
#include "SqliteDataBase.h"

class StatisticsManager
{
public:
	void operator=(const StatisticsManager&) = delete;

	// Public static function to get the singleton instance
	static StatisticsManager& getInstance() {
		static StatisticsManager instance;
		return instance;
	}

	std::vector<std::string> getHighScore() const;
	std::vector<std::string> getUserStatistics(const std::string& username) const;

private:
	IDatabase* m_database;

	// Private constructor to prevent instantiation from outside
	StatisticsManager() {}

	// Private copy constructor to prevent cloning
	StatisticsManager(const StatisticsManager&);
};