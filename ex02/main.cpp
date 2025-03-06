#include "PmergeMe.hpp"

int main(int argc, char **argv) {
	if (argc < 2)
		return 1;

	try {
		std::vector<int> v;
		std::list<int> lst;

		PmergeMe::check_input(argc, argv);
		PmergeMe::print_before(argc, argv);
		
		long microseconds = PmergeMe::get_time();

		PmergeMe::fill_vector(argc, argv, v);
		PmergeMe::sort_vector(v);
		PmergeMe::print_after(v);

		long microseconds2 = PmergeMe::get_time();

		std::cout << "Time to process a range of " << v.size() << " elements with std::vector : " \
			<< microseconds2 - microseconds << " μs" << std::endl;

		PmergeMe::fill_list(argc, argv, lst);
		PmergeMe::sort_list(lst);

		long microseconds3 = PmergeMe::get_time();

		std::cout << "Time to process a range of " << lst.size() << " elements with std::list   : " \
			<< microseconds3 - microseconds2 << " μs" << std::endl;
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
