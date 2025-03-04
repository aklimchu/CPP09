#include "RPN.hpp"

std::string RPN::arg;
std::stack<int> RPN::result;

//-------------------------------Member functions------------------------------//


void RPN::check_input(int argc, char **argv) {
	if (argc > 2)
		throw InputError();
	
	std::string arg(argv[1]);
	arg.clear();

	for (size_t i = 0; argv[1][i]; i++) {
		if (argv[1][i] != ' ') {
			arg.push_back(argv[1][i]);
		}
	}

	if (arg.size() < 3 || !std::isdigit(arg[0]) || !std::isdigit(arg[1]))
		throw InputError();
	
	for (size_t i = 2; i < arg.size(); i++) {
		if (!std::isdigit(arg[i]) && arg[i] != '/' && arg[i] != '*' && \
			arg[i] != '-' && arg[i] != '+') {
			throw InputError();
		}
	}

	size_t numbers = 0;
	size_t operators = 0;

	for (size_t i = 0; i < arg.size(); i++) {
		if (std::isdigit(arg[i]))
			numbers++;
		else
			operators++;
	}
	if (numbers != operators + 1)
			throw InputError();
}

void RPN::calculate(int argc, char **argv) {
	(void)argc;
	(void)argv;
}