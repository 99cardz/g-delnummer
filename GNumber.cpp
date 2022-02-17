#include "GNumber.hpp"
#include <iostream>


GNumber::GNumber(unsigned long long n)
{
	do m_digits += n % 10;
	while (n /= 10);
}

unsigned long GNumber::size() const { return m_digits.size(); }

char GNumber::operator[](const unsigned int& i) const
{
	if (i >= m_digits.size())
		return 0;
	return m_digits[i]; 
}

GNumber& GNumber::operator*=(const GNumber& b)
{
	*this = *this * b;
	return *this;
}

GNumber GNumber::operator*(const GNumber& b) const
{
	const GNumber& a = *this;
	GNumber result;
	const unsigned long aSize = a.size(), bSize = b.size();
	unsigned int carry;
	result.m_digits.resize(aSize + bSize);
	for (unsigned long b_i = 0; b_i < bSize; b_i++)
	{
		carry = 0;
		for (unsigned long a_i = 0; a_i < aSize; a_i++)
		{
			result.m_digits[a_i + b_i] += a[a_i] * b[b_i] + carry;
			carry = result.m_digits[a_i + b_i] / 10;
			result.m_digits[a_i + b_i] = result.m_digits[a_i + b_i] % 10;
		}
		result.m_digits[b_i + aSize] = carry;
	}
	if (result.m_digits.back() == 0)
		result.m_digits.pop_back();
	return result;
}


void GNumber::add_factor(const unsigned long& prime, unsigned long exponent)
{
	GNumber gPrime(prime);
	while (exponent--)
		*this *= gPrime;
}

std::ostream& operator<<(std::ostream& out, const GNumber& gn)
{
	unsigned long idx = gn.size();
	while (idx--)
		out << short(gn[idx]);
	return out;
}

bool GNumber::operator==(const GNumber& b) const
{
	return m_digits == b.m_digits;
}
