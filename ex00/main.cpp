#include "BitcoinExchange.hpp"

int main (int argc, char *argv[]) {
	if (argc !=2) {
		std::cout << "Error: incorrect number of arguments" << std::endl;
		return 1;
	}

	try {	
		BitcoinExchange::find_btc_price(argv[1]);
	}
	catch (BitcoinExchange::EmptyInfile & e) {
		std::cerr << e.what() << std::endl;
	}
	catch (BitcoinExchange::EmptyDatabase & e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}