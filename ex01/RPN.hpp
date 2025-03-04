#pragma once

#include <iostream>
#include <stack>

class RPN {
	public:
		RPN(void) = delete; // Canonical
		RPN(int const n) = delete;
		RPN(RPN const & src) = delete; // Canonical
		~RPN(void) = delete; // Canonical

		RPN & operator=(RPN const & rhs) = delete; // Canonical
		
		static void check_input(int argc, char **argv);
		static void calculate(int argc, char **argv);

		class InputError: public std::exception {
			public:
				virtual const char* what() const throw() {
					return ("Error");
				}
		};

	private:
		static std::string arg;
		static std::stack<int> result;
};