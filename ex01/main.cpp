#include "RPN.hpp"

int main (int argc, char **argv) {
		if (argc < 2)
		return 1;

	try {
		std::string arg(argv[1]);

		arg.clear();
		RPN::check_input(argc, argv, &arg);
		RPN::calculate(arg);
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}