#include "PmergeMe.hpp"

//-------------------------------Member functions------------------------------//

void PmergeMe::check_input(int argc, char **argv)
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
		}
		catch (...) {
			throw PmergeMe::InputError();
		}
	}
}

void PmergeMe::fill_vector(int argc, char **argv, std::vector<int> & v) {
	for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
		v.push_back(std::stoi(arg));
	}
}

void PmergeMe::sort_vector(std::vector<int> & v) {
	std::vector<int> larger_elements;

	if (v.size() == 1) {
		return;
	}
	v_sort_pairs(v);
	v_breaking_into_two(v, larger_elements);
	v_sort_smaller(v);
	v_binary_insertion(v, larger_elements);
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
			if (*itl < *mid) {
				if (mid == v.begin() || (prev_comp_larger == 1 && mid - prev_min_mid == 1)) {
					v.insert(mid, *itl);
					break;
				}
				else {
					subrange = mid - prev_min_mid;
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
		itl++;
	}
}

void PmergeMe::fill_list(int argc, char **argv, std::list<int> &lst) {
	for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
		lst.push_back(std::stoi(arg));
	}
}

void PmergeMe::sort_list(std::list<int> & lst) {
	std::list<int> larger_elements;

	if (lst.size() == 1) {
		return;
	}
	lst_sort_pairs(lst);
	lst_breaking_into_two(lst, larger_elements);
	lst_sort_smaller(lst);
	lst_binary_insertion(lst, larger_elements);
}

void PmergeMe::lst_sort_pairs(std::list<int> & lst) {
	std::list<int>::iterator it = lst.begin();
	std::list<int>::iterator ite = lst.end();
	
	while (it != std::next(ite, -1)) {
		if (*it > *std::next(it, 1)) {
			std::swap(*it, *std::next(it, 1));
		}
		if (it == std::next(ite, -2))
			break;
		it = std::next(it, 2);
	}
}

void PmergeMe::lst_breaking_into_two(std::list<int> & lst, \
	std::list<int> & larger_elements) {
	std::list<int>::iterator it = lst.begin();
	std::list<int>::iterator ite = lst.end();
	size_t i = 0;

	while (it != ite) {
		std::swap(*it, *std::next(it, -i));
		larger_elements.push_back(*std::next(it, 1));
		it = std::next(it, 2);
		i++;
		if (it == std::next(ite, -1)) {
			larger_elements.push_back(*it);
			break;
		}
	}

	lst.erase(std::next(lst.begin(), lst.size() / 2), lst.end());	
}

void PmergeMe::lst_sort_smaller(std::list<int> & lst) {
	std::list<int>::iterator it = std::next(lst.begin(), 1);
	std::list<int>::iterator ite = lst.end();
	std::list<int>::iterator ittemp = it;

	while (it != ite) {
		while (std::distance(lst.begin(), ittemp) > 0 && *ittemp < *std::next(ittemp, -1)) {
			std::swap(*ittemp, *std::next(ittemp, -1));
			ittemp--;
		}
		it++;
		ittemp = it;
	}
}

void PmergeMe::lst_binary_insertion(std::list<int> & lst, \
	std::list<int> & larger_elements) {
	std::list<int>::iterator itl = larger_elements.begin();
	std::list<int>::iterator itel = larger_elements.end();
	std::list<int>::iterator mid;
	std::list<int>::iterator prev_max_mid;
	std::list<int>::iterator prev_min_mid;
	size_t subrange;
	int prev_comp_larger;

	while (itl != itel) {
		prev_comp_larger = -1;
		if (lst.size() % 2)
			mid = std::next(lst.begin(), lst.size() / 2);
		else
			mid = std::next(lst.begin(), lst.size() / 2 - 1);
		prev_max_mid = std::next(lst.end(), -1);
		prev_min_mid = lst.begin();
		while (1) {
			if (*itl < *mid) {
				if (mid == lst.begin() || (prev_comp_larger == 1 && std::distance(prev_min_mid, mid) == 1)) {
					lst.insert(mid, *itl);
					break;
				}
				else {
					subrange = std::distance(prev_min_mid, mid);
					if (subrange % 2 || subrange == 1)
						subrange++;
					prev_max_mid = mid;
					mid = std::next(mid, subrange / 2 * (-1));
					prev_comp_larger = 0;
				}
			}
			else if (*itl > *mid) {
				if (mid == std::next(lst.end(), -1) || (prev_comp_larger == 0 && std::distance(mid, prev_max_mid) == 1)) {
					lst.insert(std::next(mid, 1), *itl);
					break;
				}
				else {
					subrange = std::distance(mid, prev_max_mid);
					if (subrange % 2 || subrange == 1)
						subrange++;
					prev_min_mid = mid;
					mid = std::next(mid, subrange / 2);
					prev_comp_larger = 1;
				}
			}
			else {
				lst.insert(mid, *itl);
				break;
			}
		}
		itl++;
	}
}

void PmergeMe::print_before(int argc, char **argv) {
	std::cout << "Before: ";
	for (int i = 1; i < argc; i++) {
		std::cout << argv[i] << " ";
	}
	std::cout << std::endl;
}

long PmergeMe::get_time(void) {
	auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    return (std::chrono::duration_cast<std::chrono::microseconds>(duration).count());
}