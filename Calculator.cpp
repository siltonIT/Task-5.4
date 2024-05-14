#include "Calculator.h"

bool Calculator::solve_expression(const std::string& expression) {
	transform_to_RPN(expression);

	const size_t TRUE = 1;
	const size_t FALSE = 0;
	
	std::vector<std::string> tokens = split_into_tokens(_RPN_expression);
	std::stack<int> sequence_numbers;
	
	for (size_t i = 0; i < tokens.size(); ++i) {
		if (tokens[i] == "")
			continue;
		
		if (is_number(tokens[i]))
			sequence_numbers.push(std::stoi(tokens[i]));
		else {
			int a = sequence_numbers.top();
			sequence_numbers.pop();

			if (tokens[i] == "!") {
				a == 0 ? sequence_numbers.push(TRUE) : sequence_numbers.push(FALSE);
				continue;
			}

			int b = sequence_numbers.top();
			sequence_numbers.pop();

			if (tokens[i] == "<")
				b < a ? sequence_numbers.push(TRUE) : sequence_numbers.push(FALSE);
			else if (tokens[i] == ">")
				b > a ? sequence_numbers.push(TRUE) : sequence_numbers.push(FALSE);
			else if (tokens[i] == "<=")
                                b <= a ? sequence_numbers.push(TRUE) : sequence_numbers.push(FALSE);
			else if (tokens[i] == ">=")
                                b >= a ? sequence_numbers.push(TRUE) : sequence_numbers.push(FALSE);
			else if (tokens[i] == "==")
                                b == a ? sequence_numbers.push(TRUE) : sequence_numbers.push(FALSE);
			else if (tokens[i] == "!=")
                                b != a ? sequence_numbers.push(TRUE) : sequence_numbers.push(FALSE);
			else if (tokens[i] == "&&")
                                b && a ? sequence_numbers.push(TRUE) : sequence_numbers.push(FALSE);
			else if (tokens[i] == "||")
                                b || a ? sequence_numbers.push(TRUE) : sequence_numbers.push(FALSE);
		}
	}
	
	if(sequence_numbers.empty())
		abort();

	return sequence_numbers.top() != 0;
}

bool Calculator::is_number(const std::string& token) {
	try {
		int num = std::stoi(token);
		return true;
	} catch (...) {
		return false;
	}
}

void Calculator::replace_keywords(std::string& token) {
	if (token == "true")
		token = "1";
	else if (token == "false")
		token = "0";
}

std::vector<std::string> Calculator::split_into_tokens(const std::string& expression) {
	std::vector<std::string> tokens;

	std::string temp = "";
	for (size_t i = 0; i < expression.size(); ++i) {
		if (expression[i] == ' ') {
			replace_keywords(temp);
			tokens.push_back(temp);
			temp = "";
			continue;
		} else if (expression[i] == ')') {
			tokens.push_back(temp);
			temp = expression[i];
			
			do {
				tokens.push_back(temp);
			} while (++i < expression.size() && expression[i] != ' ');
			
			temp = "";
			continue;
		}

		temp += expression[i];
		
		if (expression[i] == '(') {
			tokens.push_back(temp);
			temp = "";
		}

		if (i < expression.size() && (expression[i] == '!' && expression[i + 1] != '=')) {
			tokens.push_back(temp);
			temp = "";
		}
	}

	if (temp != "") {
		replace_keywords(temp);
		tokens.push_back(temp);
	}

	return tokens;
}

void Calculator::transform_to_RPN(const std::string& expression) {
	std::vector<std::string> tokens = split_into_tokens(expression);
	std::stack<std::string> sequence_operators;
	Operators operators;	

	for (size_t i = 0; i < tokens.size(); ++i) {
		if (tokens[i] == ")") {
			while (sequence_operators.top() != "(") {
				_RPN_expression += sequence_operators.top();
				_RPN_expression += ' ';
				sequence_operators.pop();
			}
			
			sequence_operators.pop();
		} else if (!is_operator(tokens[i])) {
			_RPN_expression += tokens[i];
			_RPN_expression += ' ';
		} else {
			if (sequence_operators.empty() || tokens[i] == "(" || operators.get_priority(tokens[i]) > operators.get_priority(sequence_operators.top()))
				sequence_operators.push(tokens[i]);
			else {
				while (operators.get_priority(tokens[i]) <= operators.get_priority(sequence_operators.top())) {
					_RPN_expression += sequence_operators.top();
					_RPN_expression += ' ';
					sequence_operators.pop();
					
					if(sequence_operators.empty()) 
						break;
				}

				sequence_operators.push(tokens[i]);
			}	
		}	
	}

	while (true) {
		_RPN_expression += sequence_operators.top();
		
		sequence_operators.pop();
		if (sequence_operators.empty())
			break;

		_RPN_expression += " ";
	}
}

bool Calculator::is_operator(const std::string& token) {
	Operators operators;
	
	for (size_t i = 0; i < operators.size(); ++i)
		if (token == operators[i]._simb)
			return true;

	return false;
}
