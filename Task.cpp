#include "Task.h"

int main() {
	std::cout << "Write boolean expression: " << std::endl;
	std::string expression;
	std::getline(std::cin, expression);
	
	Calculator calculator;
	calculator.solve_expression(expression) ? std::cout << "true" << std::endl : std::cout << "false" << std::endl;
}
