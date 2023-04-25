#include <string>
#include <iostream>

class IDatabse
{
public:
	
	virtual bool open() = 0;
	virtual void close() = 0;
	virtual void clear() = 0;
	virtual bool doesUserExist(const std::string& username) = 0;
	virtual bool isPasswordValid(const std::string& username, const std::string& password) = 0;
	virtual void insertUserIntoDB(const std::string& username, const std::string& password, const std::string& email) = 0;
};

