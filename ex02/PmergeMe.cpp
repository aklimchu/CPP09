#include "PmergeMe.hpp"

//--------------------------------Constructors--------------------------------//

PmergeMe::PmergeMe() {
	std::cout << "Default constructor PmergeMe called" << std::endl << std::endl;
}

PmergeMe::PmergeMe(int const arg) : _member(arg) {
	std::cout << "Parametric constructor PmergeMe called" << std::endl << std::endl;
}

PmergeMe::PmergeMe(PmergeMe const & src) {
	std::cout << "Copy constructor PmergeMe called" << std::endl << std::endl;
	*this = src;
}

//---------------------------------Destructor---------------------------------//

PmergeMe::~PmergeMe() {
	std::cout << "Destructor PmergeMe called" << std::endl << std::endl;
}

//-------------------------Copy assignment operator---------------------------//

PmergeMe & PmergeMe::operator=(PmergeMe const & rhs) {
	std::cout << "Copy assignment operator PmergeMe called" << std::endl << std::endl;
	if (this != &rhs)
		this->_member = rhs.getmember();
	return *this;
}

//-------------------------------Member functions------------------------------//