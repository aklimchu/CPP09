#pragma once

#include <iostream>
#include <fstream>
#include <vector>

class BitcoinExchange {
	public:
		BitcoinExchange(void) = delete; // Canonical
		BitcoinExchange(BitcoinExchange const & src) = delete; // Canonical
		~BitcoinExchange(void) = delete; // Canonical

		BitcoinExchange & operator=(BitcoinExchange const & rhs) = delete; // Canonical

		static void find_btc_price(std::string infile);

		class DatabaseAccess : public std::exception {
			public:
				virtual const char* what() const throw() {
					return ("Error: can't access database");
				}
		};

		class InfileAccess : public std::exception {
			public:
				virtual const char* what() const throw() {
					return ("Error: can't access incoming file");
				}
		};

		class EmptyInfile : public std::exception {
			public:
				virtual const char* what() const throw() {
					return ("Error: incoming file is empty");
				}
		};

		class EmptyDatabase : public std::exception {
			public:
				virtual const char* what() const throw() {
					return ("Error: database is empty");
				}
		};

		class EmptyLine : public std::exception {
			public:
				virtual const char* what() const throw() {
					return ("Error: line is empty");
				}
		};

		class NotPositive : public std::exception {
			public:
				virtual const char* what() const throw() {
					return ("Error:  not a positive number");
				}
		};

		class TooLarge : public std::exception {
			public:
				virtual const char* what() const throw() {
					return ("Error: too large a number");
				}
		};

		class BadInput : public std::exception {
			public:
				virtual const char* what() const throw() {
					return ("Error: bad input");
				}
		};

	private:
		static std::vector <std::string> line_divided;
		static std::ifstream input_stream;
		static std::ifstream database_stream;

		static void check_infiles(std::string infile);
		static void analyze_line(std::string line);
};