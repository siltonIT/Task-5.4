#pragma once

#include <vector>
#include <string>
#include "Operator.h"

struct Operators {
	std::vector<Operator> _operators;

	Operators();

	Operator operator[](const size_t&);

	const Operator operator[](const size_t&) const;

	size_t get_priority(const std::string&);

	size_t size() const;
};
