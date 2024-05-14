#pragma once 

#include <string>

#define size_t unsigned int

struct Operator {
	size_t _priority;
	std::string _simb;
};
