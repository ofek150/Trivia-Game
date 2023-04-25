#pragma once
#include <ctime>
#include <vector>

struct RequestInfo {
	int id;
	std::time_t arrival_time;
	std::vector<unsigned char> buffer;
};