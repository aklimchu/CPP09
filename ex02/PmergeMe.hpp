#pragma once

#include <iostream>

class PmergeMe {
	public:
		PmergeMe(void); // Canonical
		PmergeMe(int const n);
		PmergeMe(PmergeMe const & src); // Canonical
		~PmergeMe(void); // Canonical

		PmergeMe & operator=(PmergeMe const & rhs); // Canonical

		int getFoo(void) const;

	private:
		int _Foo;
};