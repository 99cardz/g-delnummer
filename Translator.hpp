#pragma once
#include <vector>
#include <istream>
#include <sstream>
#include <ostream>
#include <map>
#include <regex>
#include <string>
#include <iostream>
#include <iomanip>

/**
 * @brief Class that handles the sanitation, tranformation, validation and translation.
 * 
 * The stored chars and their values come from a istream provided to the constructor.
 * the char s and 0 are hardcoded and should be included with the istream,
 * otherwise they will be added with the next best value that is not already included.
 */
class Translator
{
private:
	std::map<char, unsigned int> m_char_values;

	const std::regex m_num_regex = std::regex("\\d+");

	unsigned int m_max_value_width;

	std::string m_all_chars;
public:
	/**
	 * @brief Construct a Instance and extract Chars and Values from input stream.
	 * 
	 * @param istream the inputstream to extract the chars from.
	 * @pre first comes the char, then its value, comments start with #
	 */
	Translator(std::istream& istream);

	/**
	 * @brief Provides the width of the highest value.
	 * 
	 * @return width 
	 */
	const unsigned int& valueMaxWidth() const;

	/**
	 * @brief Provides all defined chars as a string.
	 * 
	 * @return allChars
	 */
	const std::string& allChars() const;

	/**
	 * @brief Removes whitespaces and leading zeros.
	 * 
	 * @param term as string to be sanitised.
	 * @return the sanitised string
	 */
	std::string sanitise(std::string term) const;

	/**
	 * @brief Place numbers at their future position.
	 * 
	 * @param term a sinitised string with or without numbers
	 * @return string prettified
	 */
	std::string prettify(const std::string& term) const;

	/**
	 * @brief Finds and marks invalid chars in given string.
	 * 
	 * Valid chars are the provided chars stored, whitespace and digits.
	 * @param term as const string reference that will be checked.
	 * @param error as string reference that gets cleared and filled with '^' chars to indicate where the invalid chars are located.
	 * @return boolean value if any invalid chars where found.
	 */
	bool find_invalid_chars(const std::string& term, std::string& error) const;

	/**
	 * @brief Convert all numbers in a string to conform to successor-to-zero scheme.
	 * 
	 * 's' being the successor char and '0' the Zero char.
	 * 's' and '0' must be provided to the constructor.
	 * @param term as a string reference to be modified.
	 * @return converted string
	 */
	std::string convert_numbers(const std::string& term) const;

	/**
	 * @brief Convert a string of valid chars to a vector of corresponding values.
	 * 
	 * @param term as const string reference to be converted.
	 * @pre term must only include valid chars
	 * @return vector<int> filled with values of term.
	 */
	std::vector<unsigned int> term_to_values(const std::string& term) const;

	/**
	 * @brief Function that replaces all matched strings in the target string with a modified string.
	 * 
	 * @param target the string to be worked on.
	 * @param regex the regular expression used.
	 * @param modifier anonymus function that takes the matched string and returns a modified string.
	 * @return the resulting string.
	 */
	std::string replace_modified(std::string target, const std::regex& regex, const std::function<std::string(std::string)>& modifier) const;
};

