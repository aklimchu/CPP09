#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <cmath> // for std::pow()
#include <chrono> // for system clock

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

		static void check_input(int argc, char **argv);
		static void fill_vector(int argc, char **argv, std::vector<int> & v);
		static void sort_vector(std::vector<int> & v);
		static void v_sort_pairs(std::vector<int> & v);
		static void v_breaking_into_two(std::vector<int> & v, \
			std::vector<int> & larger_elements);
		static void v_sort_smaller(std::vector<int> & v);
		static void v_binary_insertion(std::vector<int> & v, \
			std::vector<int> & larger_elements);

		static void fill_list(int argc, char **argv, std::list<int> &lst);
		static void sort_list(std::list<int> & lst);
		static void lst_sort_pairs(std::list<int> & lst);
		static void lst_breaking_into_two(std::list<int> & lst, \
			std::list<int> & larger_elements);
		static void lst_sort_smaller(std::list<int> & lst);
		static void lst_binary_insertion(std::list<int> & lst, \
			std::list<int> & larger_elements);

		static void print_before(int argc, char **argv);
		static long get_time(void);

		template <typename T>
		static void print_after(const T& data) {
			std::cout << "After:  ";
			for (const int& num : data) {
				std::cout << num << " ";
			}
			std::cout << std::endl;
		}
};