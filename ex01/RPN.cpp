#include "RPN.hpp"

//-------------------------------Member functions------------------------------//


void RPN::check_input(int argc, char **argv, std::string *arg) {
	if (argc > 2)
		throw InputError();

	for (size_t i = 0; argv[1][i]; i++) {
		if (argv[1][i] != ' ') {
			arg->push_back(argv[1][i]);
		}
	}

	if (arg->size() < 3 || !std::isdigit((*arg)[0]) || !std::isdigit((*arg)[1]))
		throw InputError();
	
	for (size_t i = 2; i < (*arg).size(); i++) {
		if (!std::isdigit((*arg)[i]) && (*arg)[i] != '/' && (*arg)[i] != '*' && \
			(*arg)[i] != '-' && (*arg)[i] != '+') {
			throw InputError();
		}
	}

	size_t numbers = 0;
	size_t operators = 0;

	for (size_t i = 0; i < arg->size(); i++) {
		if (std::isdigit((*arg)[i]))
			numbers++;
		else
			operators++;
	}
	if (numbers != operators + 1)
			throw InputError();
}

void RPN::calculate(std::string arg) {
	std::stack<int> stack;
	
	//std::cout << arg << std::endl; // delete

	for (char elem : arg) {
		if (std::isdigit(elem)) {
			//std::cout << stack.size() << std::endl;
			stack.push(elem - '0');
		}
		else if (!std::isdigit(elem)) {
			arithmetic_operation(stack, elem);
		}
	}
	//std::cout << stack.size() << std::endl;
	std::cout << stack.top() << std::endl;
}

void RPN::arithmetic_operation(std::stack<int> & stack, char elem) {
	int temp;

	switch (elem) {
		case 43: // +
		temp = stack.top();
		stack.pop();
		temp = stack.top() + temp;
		stack.pop();
		stack.push(temp);
		break;
		case 45: // -
		temp = stack.top();
		stack.pop();
		temp = stack.top() - temp;
		stack.pop();
		stack.push(temp);
		break;
		case 42: // *
		temp = stack.top();
		stack.pop();
		temp = stack.top() * temp;
		stack.pop();
		stack.push(temp);
		break;
		case 47: // /
		temp = stack.top();
		stack.pop();
		temp = stack.top() / temp;
		stack.pop();
		stack.push(temp);
		break;
		default:
		std::cout << "Arithmetic operator not found" << std::endl;
	}
}