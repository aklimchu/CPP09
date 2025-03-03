#include "BitcoinExchange.hpp"

std::ifstream BitcoinExchange::input_stream;
std::ifstream BitcoinExchange::database_stream;
std::vector <std::string> BitcoinExchange::line_divided;
std::vector <std::string> BitcoinExchange::date_divided;

////////////////LEAKS!!!

//-------------------------------Member functions------------------------------//

void BitcoinExchange::find_btc_price(std::string infile) {
	try {
		check_infiles(infile);
	}
	catch (std::exception & e) {
		throw;
	}

	std::string line;
	if (!getline(input_stream, line)) {
		throw EmptyInfile();
	}

	if (!getline(database_stream, line)) {
		throw EmptyDatabase();
	}
	
	while (getline(input_stream, line)) {
		try {
			analyze_line(line);
			modify_line();
			
			//std::cout << line << std::endl;
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
	line_divided = ft_split(line, '|');
	if (line_divided.size() != 2)
		throw BadInput();
	try {
		check_date(line_divided[0]);
		check_amount(line_divided[1]);
	}
	catch (...) {
		throw;
	}
}

std::vector<std::string> & BitcoinExchange::ft_split(std::string & line, const char & sep)
{
    std::vector<std::string> *v = new std::vector<std::string>;
    size_t start;
    size_t end = 0;

    while ((start = line.find_first_not_of(sep, end)) != std::string::npos)
    {
        end = line.find(sep, start);
        v->push_back(line.substr(start, end - start));
    }
    return *v;
}

void BitcoinExchange::check_date(std::string str) {
		int year = 0;
		int month = 0;
		int day = 0;

	    date_divided = ft_split(str, '-');

		if (date_divided.size() != 3)
			throw BadInput();
		try {
			size_t pos;

			year = std::stoi(date_divided[0], &pos);
        	if (pos != date_divided[0].size())
            	throw BadInput();

			month = std::stoi(date_divided[1], &pos);
        	if (pos != date_divided[1].size())
            	throw BadInput();

			day = std::stoi(date_divided[2], &pos);
        	if (pos != date_divided[2].size() - 1 || date_divided[2].back() != ' ')
            	throw std::exception();
		}
		catch (...) {
			throw;
		}

		if (year < 2008 || year > 2025 || month < 1 || month > 12 \
			|| day < 1 || day > 31) {
			throw BadInput();
		}

		if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
			throw BadInput();
		
		if (((month == 2 || year % 4 == 0) && day > 29) || \
			(month == 2 && day > 28))
			throw BadInput();

}


void BitcoinExchange::check_amount(std::string str) {
	double amount = 0;

	try {
		size_t pos;
        amount = std::stof(str, &pos);

        if (pos != str.size())
            throw BadInput();
	}
	catch (...) {
		throw BadInput();
	}
	if (amount > std::numeric_limits<int>::max())
		throw TooLarge();

	if (amount < 0)
		throw NotPositive();

}

void BitcoinExchange::modify_line(void) {
	std::string database_line;
	bool line_found = false;
	double price = 0;
	double amount = 0;

	database_stream.clear();
	database_stream.seekg(0, std::ios::beg);

	while (getline(database_stream, database_line)) {
		if ((line_divided[0].substr(0, 10) == database_line.substr(0, 10))) {
			std::cout << line_divided[0] << "=>" << line_divided[1] << " = ";
			line_found = true;
			break;
		}
	}

	if (!line_found)
		//database_line = find_previous_line();
	{
		std::cout << "Line not found" << std::endl;
		return;
	}
	

	try {
		std::string price_str = database_line.substr(11, database_line.size() - 11);
		price = std::stof(price_str);
		//delete &price_str; do we need?
		amount = std::stof(line_divided[1]);
	}
	catch (...) {
		throw;
	}

	std::cout << price * amount << std::endl;
}