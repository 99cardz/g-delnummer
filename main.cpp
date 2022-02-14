#include <iostream>
#include <vector>
#include <fstream>
#include "Primes.hpp"
#include "Translator.hpp"
#include "GNumber.hpp"


/**
 * @brief print a formatted line to the console.
 * 
 * @param comment
 * @param content any iterable type
 * @param columnwidth the width for each column that the content gets devided to.
 */
template<typename Iterable>
void print_term(const std::string& comment, const Iterable& content, const unsigned int& columnwidth);


int main() 
{
	// initialise Prime Container and Translator
	std::ifstream primeFile("primzahlen.txt");
	std::ifstream valueFile("zuweisungen.txt");
	Primes primes(primeFile);
	Translator translator(valueFile);

	const unsigned int columnWidth = translator.valueMaxWidth();
	
	// reserve space for reused variables
	std::string term, termPretty, error;
	std::vector<unsigned int> values;
	GNumber gnumber;

	// run until user terminates
	while (true)
	{
		std::cout << std::endl << "Geben Sie einen Term ein [oder leere Eingabe zum Stop]: ";
		std::getline(std::cin, term);
		
		term = translator.sanitise(term);

		if (term.empty())
			return 0;

		termPretty = translator.prettify(term);
		print_term("Eingabe, getrennt:", termPretty, columnWidth);

		if (translator.find_invalid_chars(termPretty, error))
		{
			print_term("Unbekannte Zeichen:", error, columnWidth);
			std::cout << "Alle zugewiesenen Zeichen aus 'zuweisungen.txt': " << translator.allChars() << std::endl;
			continue;
		}

		term = translator.convert_numbers(term);
		print_term("Term mit convertierten Zahlen:", term, columnWidth);

		values = translator.term_to_values(term);
		print_term("Term als Zahlen:", values, columnWidth);

		primes.reset();
		gnumber = 1;
		for (const unsigned int& v : values)
			gnumber *= GNumber::simple_pow(primes.next(), v);
		
		std::cout << std::endl << "Goedelnummer fuer den Term: " << gnumber << std::endl << std::endl;
	}
}


template<typename Iterable>
void print_term(const std::string& comment, const Iterable& content, const unsigned int& columnwidth)
{
	std::cout << std::setw(35) << std::left << comment;

	std::cout << '|';
	for (const auto item : content)
		std::cout << std::right << std::setw(columnwidth) << item << '|';
	
	std::cout << std::endl;
}