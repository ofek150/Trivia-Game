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
    if (argv[0] == NULL) throw std::exception("Encountered an error while retrieving data");
    if (argc > 0) *num = atoi(argv[0]);
    return 0;
}

int callbackDouble(void* data, int argc, char** argv, char** azColName)
{
    double* num = static_cast<double*>(data);
    if (argc > 0) *num = strtod(argv[0], nullptr);
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
        sqlStatement = "CREATE TABLE USERS (USERNAME TEXT NOT NULL PRIMARY KEY UNIQUE, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL)";
        res = sqlite3_exec(db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
        if (res != SQLITE_OK)
        {
            std::cerr << errMessage << std::endl;
            return false;
        }
        sqlStatement = "CREATE TABLE QUESTIONS (ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, CATEGORY TEXT NOT NULL, QUESTIONS TEXT NOT NULL UNIQUE, A TEXT NOT NULL, B TEXT NOT NULL, C TEXT NOT NULL, D TEXT NOT NULL, ANSWER INTEGER NOT NULL)";
        res = sqlite3_exec(db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
        if (res != SQLITE_OK)
        {
            std::cerr << errMessage << std::endl;
            return false;
        }
        sqlStatement = "CREATE TABLE STATISTICS(USERNAME INTEGER NOT NULL, NUM_OF_GAMES  INTEGER NOT NULL, AVG_TIME  FLOAT NOT NULL, CORRECT_ANSWERS  INTEGER NOT NULL, WRONG_ANSWERS INTEGER NOT NULL, FOREIGN KEY(USERNAME) REFERENCES USERS(USERNAME));";
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

int SqliteDataBase::getNumOfPlayerGames(const std::string username)
{
    int numOfGames = 0;
    std::string sqlStatement = "SELECT NUM_OF_GAMES FROM STATISTICS WHERE USERNAME = '" + username + "';";
    char* errMessage = nullptr;
    int res = sqlite3_exec(db, sqlStatement.c_str(), callbackInteger, &numOfGames, &errMessage);
    if (res != SQLITE_OK) std::cerr << errMessage << std::endl;
    return numOfGames;
}

int SqliteDataBase::getNumOfTotalAnswers(const std::string username)
{
    int total_answers = 0;
    std::string sqlStatement = "SELECT SUM(CORRECT_ANSWERS + WRONG_ANSWERS) FROM STATISTICS WHERE USERNAME = '" + username + "';";
    char* errMessage = nullptr;
    int res = sqlite3_exec(db, sqlStatement.c_str(), callbackInteger, &total_answers, &errMessage);
    if (res != SQLITE_OK) std::cerr << errMessage << std::endl;
    return total_answers;
}

int SqliteDataBase::getNumOfCorrectAnswers(const std::string username)
{
    int correct_answers = 0;
    std::string sqlStatement = "SELECT CORRECT_ANSWERS FROM STATISTICS WHERE USERNAME = '" + username + "';";
    char* errMessage = nullptr;
    int res = sqlite3_exec(db, sqlStatement.c_str(), callbackInteger, &correct_answers, &errMessage);
    if (res != SQLITE_OK) std::cerr << errMessage << std::endl;
    return correct_answers;
}

double SqliteDataBase::getPlayerAverageAnswerTime(const std::string username)
{
    double avg_time = 0;
    std::string sqlStatement = "SELECT AVG_TIME FROM STATISTICS WHERE USERNAME = '" + username + "';";
    char* errMessage = nullptr;
    int res = sqlite3_exec(db, sqlStatement.c_str(), callbackDouble, &avg_time, &errMessage);
    if (res != SQLITE_OK) std::cerr << errMessage << std::endl;
    return avg_time;
}
std::vector<std::string> SqliteDataBase::getTopUserGrades() const
{
    std::vector<std::string> userGrades;
    std::string sqlStatement = "SELECT USERNAME, ((CORRECT_ANSWERS * 1.0) / (CORRECT_ANSWERS + WRONG_ANSWERS)) / AVG_TIME * 10 AS grade "
        "FROM STATISTICS "
        "ORDER BY grade DESC "
        "LIMIT 5;";
    char* errMessage = nullptr;
    int res = sqlite3_exec(db, sqlStatement.c_str(), [](void* data, int argc, char** argv, char** azColName) {
        std::vector<std::string>* userGrades = static_cast<std::vector<std::string>*>(data);
        if (argc == 2) {
            std::string username = argv[0];
            std::string grade = argv[1];
            userGrades->push_back(username + ": " + grade);
        }
        return 0;
        }, &userGrades, &errMessage);
    if (res != SQLITE_OK) {
        std::cerr << errMessage << std::endl;
    }
    return userGrades;
}

std::vector<std::string> SqliteDataBase::getQuestions(const int amount, std::string category) const
{
    std::vector<std::string> questions;
    std::string sqlStatement = "SELECT QUESTIONS FROM QUESTIONS WHERE CATEGORY = '" + category + "' ORDER BY RANDOM() LIMIT " + std::to_string(amount) + ";";
    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        std::vector<std::string>* questionList = static_cast<std::vector<std::string>*>(data);
        if (argc > 0) {
            std::string question = argv[0];
            questionList->push_back(question);
        }
        return 0;
    };
    char* errMessage = nullptr;
    int res = sqlite3_exec(db, sqlStatement.c_str(), callback, &questions, &errMessage);
    if (res != SQLITE_OK) {
        std::cerr << errMessage << std::endl;
    }
    return questions;
}

std::vector<std::string> SqliteDataBase::getPossibleAnswers(const std::string& title) const
{
    std::vector<std::string> possibleAnswers;
    std::string sqlStatement = "SELECT A, B, C, D FROM QUESTIONS WHERE QUESTIONS = '" + title + "';";
    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        std::vector<std::string>* answerList = static_cast<std::vector<std::string>*>(data);
        for (int i = 0; i < argc; i++) {
            std::string answer = argv[i];
            answerList->push_back(answer);
        }
        return 0;
    };
    char* errMessage = nullptr;
    int res = sqlite3_exec(db, sqlStatement.c_str(), callback, &possibleAnswers, &errMessage);
    if (res != SQLITE_OK) {
        std::cerr << errMessage << std::endl;
    }

    return possibleAnswers;
}
int SqliteDataBase::getAnswerIdByTitle(const std::string& title) const 
{
    int answerId = 0;
    std::string sqlStatement = "SELECT ANSWER FROM QUESTIONS WHERE QUESTIONS = '" + title + "';";
    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        int* id = static_cast<int*>(data);
        if (argc > 0) {
            *id = std::atoi(argv[0]);
        }
        return 0;
    };
    char* errMessage = nullptr;
    int res = sqlite3_exec(db, sqlStatement.c_str(), callback, &answerId, &errMessage);
    if (res != SQLITE_OK) {
        std::cerr << errMessage << std::endl;
    }
    return answerId;
}

void SqliteDataBase::submitGameStats(std::string username, const GameData& data) const
{
    std::string sqlStatement = "UPDATE STATISTICS SET NUM_OF_GAMES = NUM_OF_GAMES + 1, "
        "AVG_TIME = ((AVG_TIME * NUM_OF_GAMES) + " + std::to_string(data.avgAnswerTime) + ") / (NUM_OF_GAMES + 1), "
        "CORRECT_ANSWERS = CORRECT_ANSWERS + " + std::to_string(data.correctAnswerCount) + ", "
        "WRONG_ANSWERS = WRONG_ANSWERS + " + std::to_string(data.wrongAnswerCount) + " "
        "WHERE USERNAME = '" + username + "';";

    char* errMessage = nullptr;
    int res = sqlite3_exec(db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
    if (res != SQLITE_OK) {
        std::cerr << errMessage << std::endl;
    }
}
