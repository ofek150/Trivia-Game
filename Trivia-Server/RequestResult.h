#pragma once

struct RequestResult {
	std::vector<unsigned char> responseBuffer;
	IRequestHandler* newHandler;
};