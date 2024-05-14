#pragma once

#include <string>
#include <vector>
#include <stack>
#include "Operators.h"

#define size_t unsigned int

class Calculator {
public:
	bool solve_expression(const std::string&);
private:
	std::string _RPN_expression;

	bool is_number(const std::string&);

	void replace_keywords(std::string&);

	std::vector<std::string> split_into_tokens(const std::string&);

	void transform_to_RPN(const std::string&);

	bool is_operator(const std::string&);
};
