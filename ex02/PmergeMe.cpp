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
	
	/* std::cout << std::endl << "Vector after sorting the pairs: ";
	for (int num : v) {
		std::cout << num << " ";
	} */

	v_breaking_into_two(v, larger_elements);

	/* std::cout << std::endl << "Larger elements: ";
	for (int num : larger_elements) {
		std::cout << num << " ";
	}

	std::cout << std::endl << "Smaller elements: ";
	for (int num : v) {
		std::cout << num << " ";
	}
 */
	v_sort_smaller(v);

	/* std::cout << std::endl << "Sorted smaller elements: ";
	for (int num : v) {
		std::cout << num << " ";
	} */

	v_binary_insertion(v, larger_elements);

	std::cout << std::endl << "Sorted vector: ";
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
	std::vector<int>::iterator it = v.begin() + 1;
	std::vector<int>::iterator ite = v.end();
	std::vector<int>::iterator ittemp = it;

	while (it != ite) {
		while (ittemp > v.begin() && *ittemp < *(ittemp - 1)) {
			std::swap(*ittemp, *(ittemp - 1));
			ittemp--;
		}
		it++;
		ittemp = it;
	}
}

void PmergeMe::v_binary_insertion(std::vector<int> & v, std::vector<int> & larger_elements) {
	std::vector<int>::iterator itl = larger_elements.begin();
	std::vector<int>::iterator itel = larger_elements.end();
	std::vector<int>::iterator mid;
	std::vector<int>::iterator prev_max_mid;
	std::vector<int>::iterator prev_min_mid;
	size_t subrange;
	int prev_comp_larger;

	while (itl != itel) {
		prev_comp_larger = -1;
		if (v.size() % 2)
			mid = v.begin() + v.size() / 2;
		else
			mid = v.begin() + v.size() / 2 - 1;
		prev_max_mid = v.end() - 1;
		prev_min_mid = v.begin();
		while (1) {
			//std::cout << std::endl << "mid = " << *mid << std::endl;
			if (*itl < *mid) {
				if (mid == v.begin() || (prev_comp_larger == 1 && mid - prev_min_mid == 1)) {
					v.insert(mid, *itl);
					break;
				}
				else {
					subrange = mid - prev_min_mid;
					//std::cout << std::endl << "subrange = " << subrange << std::endl;
					if (subrange % 2 || subrange == 1)
						subrange++;
					prev_max_mid = mid;
					mid -= subrange / 2;
					prev_comp_larger = 0;
				}
			}
			else if (*itl > *mid) {
				if (mid == v.end() - 1 || (prev_comp_larger == 0 && prev_max_mid - mid == 1)) {
					v.insert(mid + 1, *itl);
					//std::cout << "We are inserting to the end" << std::endl;
					break;
				}
				else {
					subrange = prev_max_mid - mid;
					if (subrange % 2 || subrange == 1)
						subrange++;
					prev_min_mid = mid;
					mid += subrange / 2;
					prev_comp_larger = 1;
				}
			}
			else {
				v.insert(mid, *itl);
				break;
			}
		}
		/* std::cout << std::endl << "Iterated vector: ";
		for (int num : v) {
			std::cout << num << " ";
		} */
		itl++;
	}
}