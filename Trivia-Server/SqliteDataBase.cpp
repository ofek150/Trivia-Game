#include "SqliteDataBase.h"

//callback functions:
int callbackString(void* data, int argc, char** argv, char** azColName)
{
    std::string* UserPassword = static_cast<std::string*>(data);
    if (argc > 0) *UserPassword = argv[0];
    return 0;
}
int callbackInteger(void* data, int argc, char** argv, char** azColName)
{
    int* num = static_cast<int*>(data);
    if (argc > 0) *num = atoi(argv[0]);
    return 0;
}

bool SqliteDataBase::open()
{
    std::string dbFileName = "Database/TriviaDB.sqlite";
    int fileExist = _access(dbFileName.c_str(), 0);
    int res = sqlite3_open(dbFileName.c_str(), &(db));
    if (res != SQLITE_OK)
    {
        db = nullptr;
        std::cout << "Failed to open DB" << std::endl;
        return false;
    }
    char* errMessage = nullptr;
    std::string sqlStatement;
    if (fileExist != 0)
    {
        sqlStatement = "CREATE TABLE USERS(USERNAME TEXT NOT NULL PRIMARY KEY UNIQUE, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL) ";
        res = sqlite3_exec(db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
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
    sqlite3_close(db);
    db = nullptr;
}

void SqliteDataBase::clear()
{
    const char* sqlStatement = "DELETE FROM USERS;";
    char** errMessage = nullptr;
    int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, errMessage);
    if (res != SQLITE_OK) std::cerr << "Clearing database failed.";
}

bool SqliteDataBase::doesUserExist(const std::string& username)
{
    int count = 0;
    std::string sqlStatement = "SELECT COUNT(*) FROM USERS WHERE USERNAME = '" + username + "';";
    char* errMessage = nullptr;
    int res = sqlite3_exec(db, sqlStatement.c_str(), callbackInteger, &count, &errMessage);
    if (res != SQLITE_OK) std::cerr << errMessage << std::endl;
    return count != 0;
}

bool SqliteDataBase::isPasswordValid(const std::string& username, const std::string& password)
{
    if(!doesUserExist(username)) return false;
    std::string UserPassword= "";
    std::string sqlStatement = "SELECT PASSWORD FROM USERS WHERE USERNAME = '" + username + "';";
    char* errMessage = nullptr;
    int res = sqlite3_exec(db, sqlStatement.c_str(), callbackString, &UserPassword, &errMessage);
    if (res != SQLITE_OK) std::cerr << errMessage << std::endl;
    return password == UserPassword;
}

void SqliteDataBase::insertUserIntoDB(const std::string& username, const std::string& password, const std::string& email)
{
    std::string sqlStatement = "INSERT INTO USERS (USERNAME, PASSWORD, EMAIL) VALUES ('" + username + "', '" + password + "', '" + email + "');";
    char* errMessage = nullptr;
    int res = sqlite3_exec(db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
    if (res != SQLITE_OK) std::cerr << errMessage << std::endl;
}
