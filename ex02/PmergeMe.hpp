#pragma once

#include <iostream>
#include <vector>

class PmergeMe {
	public:
		PmergeMe(void) = delete; // Canonical
		PmergeMe(int const n) = delete;
		PmergeMe(PmergeMe const & src) = delete; // Canonical
		~PmergeMe(void) = delete; // Canonical

		PmergeMe & operator=(PmergeMe const & rhs) = delete; // Canonical

		class InputError: public std::exception {
			public:
				virtual const char* what() const throw() {
					return ("Error");
				}
		};

		static void fill_containers(int argc, char **argv, std::vector<int> & v);
		static void sort_vector(std::vector<int> & v);
		static void v_sort_pairs(std::vector<int> & v);
		static void v_breaking_into_two(std::vector<int> & v, \
			std::vector<int> & larger_elements);
		static void v_sort_smaller(std::vector<int> & v);
		static void v_binary_insertion(std::vector<int> & v, \
			std::vector<int> & larger_elements);

	private:
};