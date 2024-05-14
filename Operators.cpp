#include "Operators.h"

Operators::Operators() {
	Operator op;

	op._priority = 0;
	op._simb = "(";
	_operators.push_back(op);

	op._priority = 4;
	op._simb = "!";
	_operators.push_back(op);

	op._priority = 3;
	op._simb = ">";
	_operators.push_back(op);

	op._simb = "<";
	_operators.push_back(op);

	op._simb = ">=";
	_operators.push_back(op);

	op._simb = "<=";
	_operators.push_back(op);

	op._priority = 2;
	op._simb = "==";
	_operators.push_back(op);

	op._simb = "!=";
	_operators.push_back(op);

	op._priority = 1;
	op._simb = "&&";
	_operators.push_back(op);

	op._simb = "||";
	_operators.push_back(op);

}

Operator Operators::operator[](const size_t& index) {
	return _operators[index];
}

const Operator Operators::operator[](const size_t& index) const {
	return _operators[index];
}

size_t Operators::get_priority(const std::string& key) {
	for(size_t i = 0; i < _operators.size(); ++i)
		if(_operators[i]._simb == key)
			return _operators[i]._priority;

	abort();
}

size_t Operators::size() const {
	return _operators.size();
}
