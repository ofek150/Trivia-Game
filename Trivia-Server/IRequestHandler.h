#pragma once
#include <ctime>
#include <vector>
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketSerializer.h"
#include "StatusCodes.h"
#include "RequestCodes.h"

class IRequestHandler;

struct RequestResult {
	std::vector<unsigned char> responseBuffer;
	IRequestHandler* newHandler;
};

struct RequestInfo {
	int code;
	std::time_t arrival_time;
	std::vector<unsigned char> buffer;
};


class IRequestHandler
{
public:
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) const = 0;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) const = 0;
protected:
	RequestResult ErrorResult(std::exception e) const;
};

