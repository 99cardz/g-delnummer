#include "Translator.hpp"


Translator::Translator(std::istream& stream)
{
	std::string line;
	std::smatch match;
	unsigned int maxValue = 0;

	while (std::getline(stream, line))
	{
		if (!std::regex_match(line, match, std::regex("^\\s*([^1-9])\\s+(\\d+).*$")))
			continue;

		const char c = match[1].str()[0]; // first group is char
		const unsigned int value = std::stoi(match[2].str()); // second group is value

		if (value == 0)
			std::cout << "WARNUNG: Dem Zeichen '" << c << "' wurde der Wert 0 zugewiesen." << std::endl;

		for (const auto& pair : m_char_values)
		{
			if (pair.first == c)
				std::cout << "WARNUNG: Das Zeichen '" << c << "' wurde mehrfach zugewiesen." << std::endl;
			if (pair.second == value)
				std::cout << "WARNUNG: Das Zeichen '" << c << "' hat den gleichen Wert wie das Zeichen '" << pair.first << "'." << std::endl;
		}

		m_char_values[c] = value;
		m_all_chars += c;
		maxValue = (maxValue < value) ? value : maxValue;
	}
	
	for (const char requiredChar : {'s', '0'})
		if (m_char_values.find(requiredChar) == m_char_values.end())
		{
			std::cout << "WARNUNG: Das Zeichen '" << requiredChar << "' wurde nicht zugewiesen in 'zuweisungen.txt'. ";
			std::cout << "Dem Zeichen wird der Wert " << (maxValue + 1) << " gegeben." << std::endl << std::endl;
			m_char_values[requiredChar] = ++maxValue;
		}

	m_max_value_width = std::to_string(maxValue).size();
}


const unsigned int& Translator::valueMaxWidth() const { return m_max_value_width; }

	
const std::string& Translator::allChars() const { return m_all_chars; }


std::string Translator::sanitise(std::string term) const
{
	term = std::regex_replace(term, std::regex("\\s+"), "");
	return std::regex_replace(term, std::regex("0*(\\d+)"), "$1");
}


std::string Translator::prettify(const std::string& term) const
{
	return replace_modified(term, m_num_regex, [](std::string s) { return std::string(std::stoull(s) - s.size() + 1, ' ') + s; });
}

	
bool Translator::find_invalid_chars(const std::string& term, std::string& error) const
{
	error = "";
	for (const char& c : term)
		error += (m_char_values.find(c) != m_char_values.end() || std::isspace(c) || std::isdigit(c)) ? ' ' : '^';
	return error.find('^') != std::string::npos;
}


std::string Translator::convert_numbers(const std::string& term) const
{
	return replace_modified(term, m_num_regex, [](std::string s) { return std::string(std::stoull(s), 's') + "0"; });
}


std::vector<unsigned int> Translator::term_to_values(const std::string& term) const
{
	std::vector<unsigned int> ret;
	for (const char& c : term)
		ret.push_back(m_char_values.at(c));
	return ret;
}

std::string Translator::replace_modified(std::string target, const std::regex& regex, const std::function<std::string(std::string)>& modifier) const
{
	std::string product;
	std::smatch sm;
	while (std::regex_search(target, sm, regex))
	{
        product += sm.prefix();
		product += modifier(sm.str());
        target = target.substr(sm.position() + sm.str().size());
	}
    return product += target;
}
