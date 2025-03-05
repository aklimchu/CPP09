#include "PmergeMe.hpp"

int main(int argc, char **argv) {
	if (argc < 2)
		return 1;

	try {
		std::vector<int> v;

		PmergeMe::fill_containers(argc, argv, v);

		if (argc == 2) {
			std::cout << v.front() << std::endl;
			return 0;
		}

		std::cout << "Original vector: ";
		for (int num : v) {
			std::cout << num << " ";
		}
		std::cout << std::endl;

		PmergeMe::sort_vector(v);


		// fill in the first data structure and conduct the algorithm
		// fill in the second data structure and conduct the algorithm
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
