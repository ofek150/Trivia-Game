#pragma once
#include <ctime>
#include <vector>
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketSerializer.h"

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
	virtual bool isRequestRelevant(RequestInfo requestInfo) = 0;
	virtual RequestResult handleRequest(RequestInfo requestInfo) = 0;
};

