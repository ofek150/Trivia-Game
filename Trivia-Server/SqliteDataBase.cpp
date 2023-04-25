#include "SqliteDataBase.h"

bool SqliteDataBase::open()
{
    std::string dbFileName = "MyDB.sqlite";
    int fileExist = _access(dbFileName.c_str(), 0);
    int res = sqlite3_open(dbFileName.c_str(), &(this->db));
    if (res != SQLITE_OK)
    {
        this->db = nullptr;
        std::cout << "Failed to open DB" << std::endl;
        return false;
    }
    char* errMessage = nullptr;
    std::string sqlStatement;
    if (fileExist != 0)
    {
        sqlStatement = "CREATE TABLE USERS(USERNAME TEXT NOT NULL PRIMARY KEY UNIQUE, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL) ";
        res = sqlite3_exec(this->db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
        if (res != SQLITE_OK)
        {
            std::cerr << errMessage << std::endl;
            return false;
        }
    }
    return true;
}

void SqliteDataBase::close()
{
    sqlite3_close(this->db);
    this->db = nullptr;
}

void SqliteDataBase::clear()
{
    this->close();
    this->open();
}

void SqliteDataBase::insertUserIntoDB(const std::string& username, const std::string& password, const std::string& email)
{
}

bool SqliteDataBase::doesUserExist(const std::string& username)
{
	return false;
}

bool SqliteDataBase::isPasswordValid(const std::string& username, const std::string& password)
{
	return false;
}
