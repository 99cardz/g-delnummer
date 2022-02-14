#pragma once
#include <vector>
#include <istream>

/**
 * @brief Wrapper that privides primes.
 * 
 * Primes are provided to the constructor in a istream.
 * Access to subsequent Primes is provided with the next() method.
 * If a new cycle is started, the running index can be reset with the reset() method.
 * To avoid an index error in the event of an exhaustion of primes, next ones will be calculated
 * and stored for future cycles.
 */
class Primes
{
private:
	
	/// Vector that stores the primes
	std::vector<unsigned int> m_content;

	/// index to keep track of the last retrieved prime
	unsigned int m_index = 0;

	/**
	 * @brief find next prime after provided one.
	 * 
	 * @param next the next possible prime.
	 * @return next prime.
	 */
	unsigned int find_next(const unsigned int& next);

public:
	/**
	 * @brief Construct new Container and extract Primes from input stream.
	 * 
	 * The istream should contain any number of primes (at least one) seperated by whitespaces.
	 * Commas in stream will be ignored.
	 * @param stream to provide the initial prime numbers.
	 */
	Primes(std::istream& stream);

	/**
	 * @brief Give out the next Prime.
	 * 
	 * If stored primes are exhausted, find_next is called.
	 * Increments the index to keep track.
	 * 
	 * @return prime that is stored at the current index.
	 */
	const unsigned int& next();

	/**
	 * @brief reset internal index to 0.
	 */
	void reset();
};
