#include "Primes.hpp"

Primes::Primes(std::istream& stream)
{
	std::string token;
	while (stream >> token)
		m_content.push_back(std::stoi(token));

	// for safety
	if (m_content.empty())
		m_content.push_back(2U);
}

unsigned int Primes::find_next(const unsigned int& next)
{
	for (unsigned int i = 2 ; i < next; i++)
		if (next % i == 0)
			return find_next(next + 1);
	return next;
}
	

const unsigned int& Primes::next() 
{ 
	if (m_index >= m_content.size())
		m_content.push_back(find_next(m_content.back() + 1));
	return m_content[m_index++]; 
}

	
void Primes::reset() 
{
	m_index = 0;
}