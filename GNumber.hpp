#pragma once
#include <string>
#include <vector>
#include <ostream>

/**
 * @brief Class GNumber
 * This class will store the Goedelnumber. 
 * It only provides the multiplication operator, since it is the only operation we apply to the GNumber.
 * The number will also always be positive, so no need for a signing.
 * Digits are stored in a std::string in base 10. The first Index is the rightmost decimal of the number.
 */
class GNumber
{
private:
	/// String that stores the digits of the number.
	std::string m_digits;

public:
	/**
	 * @brief Construct a new GNumber object with initial value.
	 * @param n integer to be initialised with.
	 */
	GNumber(unsigned long long n);

	/**
	 * @brief Construct a new empty GNumber object.
	 */
	GNumber() {};

	/**
	 * @brief get size of the stored digits.
	 * 
	 * @return size
	 */
	unsigned long size() const;

	/**
	 * @brief Retrieve a digit at the privided index.
	 * 
	 * @param index
	 * @return the digit, if it is stored, otherwise 0.
	 */
	char operator[](const unsigned int& index) const;

	/**
	 * @brief Multiply two GNumber objects.
	 * 
	 * Using the multipication algorithm described here:
	 * https://en.wikipedia.org/wiki/Multiplication_algorithm#Long_multiplication.
	 * 
	 * @param b GNumber to multiply with.
	 * @return resulting Gnumber.
	 */
	GNumber operator*(const GNumber& b) const;

	/**
	 * @brief Multiply this GNumber object with another GNumber
	 * 
	 * @param b GNumber to multiply with.
	 * @return resulting Gnumber.
	 */
	GNumber& operator*=(const GNumber& b);

	bool operator==(const GNumber& b) const;

	/**
	 * @brief expand this GNumber object with a new factor
	 * 
	 * @param base
	 * @param exponent
	 */
	void add_factor(const unsigned long& prime, unsigned long exponent);
};


/**
 * @brief output a GNumber to a stream
 * 
 * The digits are stored in reverse, so the largest decimal is at the end of the vector.
 * 
 * @param out the ostream to print to
 * @param gn The GNumber to print
 * @return the ostream to reuse
 */
std::ostream& operator<<(std::ostream& out, const GNumber& gn);
