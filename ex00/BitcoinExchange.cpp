#include "BitcoinExchange.hpp"

std::ifstream BitcoinExchange::input_stream;
std::ifstream BitcoinExchange::database_stream;

//-------------------------------Member functions------------------------------//

void BitcoinExchange::find_btc_price(std::string infile) {
	try {
		check_infiles(infile);
	}
	catch (std::exception & e) {
		throw;
	}

	std::string line;
	if (!getline(input_stream, line))
		throw EmptyInfile();

	if (!getline(database_stream, line))
		throw EmptyDatabase();
	
	while (getline(input_stream, line)) {
		try {
			analyze_line(line);
			// modify the line
			std::cout << line << std::endl;
		}
		catch (BitcoinExchange::BadInput & e) {
			std::cerr << e.what() << " => " << line << std::endl;
		}
		catch (std::exception & e) {
			std::cerr << e.what() << std::endl;
		}
	}
}

void BitcoinExchange::check_infiles(std::string infile) {
	
	database_stream.open("data.csv", std::ifstream::in);
	if (!database_stream)
		throw DatabaseAccess();

	input_stream.open(infile, std::ifstream::in);
	if (!input_stream)
		throw InfileAccess();
}

void BitcoinExchange::analyze_line(std::string line) {
	if (line.empty())
		throw EmptyLine();
	
}