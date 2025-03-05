#include "PmergeMe.hpp"

//-------------------------------Member functions------------------------------//

void PmergeMe::fill_containers(int argc, char **argv, std::vector<int> & v)
 {
	int temp;
	size_t pos;
	
	if (argc > 3001)
		throw PmergeMe::InputError();

	for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
		try {
			temp = std::stoi(arg, &pos);
			if (pos != arg.size() || temp <= 0)
				throw PmergeMe::InputError();
			v.push_back(temp);
		}
		catch (...) {
			throw PmergeMe::InputError();
		}
	}
}

void PmergeMe::sort_vector(std::vector<int> & v) {
	std::vector<int> larger_elements;

	v_sort_pairs(v);
	
	std::cout << std::endl << "Vector after sorting the pairs: ";
	for (int num : v) {
		std::cout << num << " ";
	}

	v_breaking_into_two(v, larger_elements);

	std::cout << std::endl << "Larger elements: ";
	for (int num : larger_elements) {
		std::cout << num << " ";
	}

	std::cout << std::endl << "Smaller elements: ";
	for (int num : v) {
		std::cout << num << " ";
	}

	v_sort_smaller(v);

	std::cout << std::endl << "Sorted smaller elements: ";
	for (int num : v) {
		std::cout << num << " ";
	}
}

void PmergeMe::v_sort_pairs(std::vector<int> & v) {
	std::vector<int>::iterator it = v.begin();
	std::vector<int>::iterator ite = v.end();
	
	while (it != ite - 1) {
		if (*it > *(it + 1)) {
			std::swap(*it, *(it + 1));
		}
		if (it == ite - 2)
			break;
		it += 2;
	}
}

void PmergeMe::v_breaking_into_two(std::vector<int> & v, std::vector<int> & larger_elements) {
	std::vector<int>::iterator it = v.begin();
	std::vector<int>::iterator ite = v.end();
	size_t i = 0;

	while (it != ite) {
		std::swap(*it, *(it - i));
		larger_elements.push_back(*(it + 1));
		it += 2;
		i++;
		if (it == ite - 1) {
			larger_elements.push_back(*it);
			break;
		}
	}

	v.erase(v.begin() + v.size() / 2, v.end());
}

void PmergeMe::v_sort_smaller(std::vector<int> & v) {

}
