#include "RPN.hpp"

int main (int argc, char **argv) {
	if (argc < 2)
		return 1;

	try {
		RPN::check_input(argc, argv);
		RPN::calculate(argc, argv);
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}