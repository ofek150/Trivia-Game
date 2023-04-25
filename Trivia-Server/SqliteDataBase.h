#pragma once
#include "IDatabase.h"
#include <string>
#include <iostream>
#include "sqlite3.h"
#include <io.h>
class SqliteDataBase : public IDatabse
{
	bool open()override;
	void close() override;
	void clear() override;
	bool doesUserExist(const std::string& username) override;
	bool isPasswordValid(const std::string& username, const std::string& password) override;
	void insertUserIntoDB(const std::string& username, const std::string& password, const std::string& email) override;
private:
	sqlite3* db; 
};

