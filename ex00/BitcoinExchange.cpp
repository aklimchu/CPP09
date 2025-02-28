#include "BitcoinExchange.hpp"

//-------------------------------Member functions------------------------------//

void BitcoinExchange::find_btc_price(std::string infile) {
	try {
		check_infiles(infile);
	}
	catch (BitcoinExchange::DatabaseAccess & e) {
		std::cerr << e.what() << std::endl;
	}
	catch (BitcoinExchange::InfileAccess & e) {
		std::cerr << e.what() << std::endl;
	}

	std::string line;
	if (!getline(input_stream, line))
		throw EmptyInfile();

	if (!getline(database_stream, line))
		throw EmptyDatabase();
	
	while (getline(input_stream, line)) {
		try {
			analyze_line(line);
		}
		catch (BitcoinExchange::EmptyLine & e) {
			std::cerr << e.what() << std::endl;
		}
		catch (BitcoinExchange::NotPositive & e) {
			std::cerr << e.what() << std::endl;
		}
		catch (BitcoinExchange::TooLarge & e) {
			std::cerr << e.what() << std::endl;
		}
		catch (BitcoinExchange::BadInput & e) {
			std::cerr << e.what() << " => " << line << std::endl;
		}
	}


	//analyze data in vector and print
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