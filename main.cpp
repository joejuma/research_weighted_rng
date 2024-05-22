#include <cstdlib>
#include <iostream>

#include <string>
#include <random>
#include <chrono>
#include <vector>
#include <map>

template <typename T>
struct FrequencyCounter
{
	std::map<T, std::uint64_t> values;

	void add(const T& value)
	{
		if (this->values.find(value) == this->values.end())
		{
			this->values[value] = 0;
		};
		this->values[value] += 1;
	};

	virtual std::string toString() = 0;
};

struct CoinFlipCounter : FrequencyCounter<bool>
{
	inline std::string toString()
	{
		uint64_t h = this->values[true];
		uint64_t t = this->values[false];
		uint64_t count = h + t;

		return (
			"{ \"heads\": (" + std::to_string(h) + "," + "P(" + std::to_string((double)h / (double)count) + "))" +
			", \"tails\": (" + std::to_string(t) + "," + "P(" + std::to_string((double)t / (double)count) + "))" +
			" }"
		);
	};
};

bool coinFlip(const double& seed = std::chrono::high_resolution_clock::now().time_since_epoch().count())
{
	std::mt19937 rng((unsigned int)seed);
	std::uniform_real_distribution<double> range(0.0, 1.0);

	if (range(rng) >= 0.5)
	{
		return true;
	}
	else
	{
		return false;
	};
};

uint64_t countBits(const uint64_t& value)
{
	/* 
		Counts the number of 1 bits in the binary representation of the given integer 
		value.
	*/

	uint64_t count = 0;
	uint64_t n = value;
	while (n)
	{
		count += (n & 1);
		n >>= 1;
	};
	return count;
};

uint64_t countBalancedCoinFlips(const uint64_t& number)
{
	/*
		Given a number of coin flips (number), counts the number of permutations 
		of that many coin-flips that will result in an equal number of heads and 
		tails outcomes.
	*/

	uint64_t balancedValue = (uint64_t)floor((double)number / 2.0); // The numeric value from summing half heads (1) and half tails (0).
	uint64_t count = 0;
	uint64_t n = (uint64_t)floor(pow(2.0, (double)number)); // The number of permutations

	for (uint64_t i = 0; i < n; i++)
	{
		uint64_t bits = countBits(i);
		if (countBits(i) == balancedValue)
		{
			count += 1;
		};

		if (i % 1000000000 == 0 && i != 0)
		{
			std::cout << "iteration " << std::to_string(i) << "\n";
		};
	};

	return count;
};

double factorial(const double& x)
{
	double y = 1;
	for (uint64_t z = x; z > 0; z--)
	{
		y *= z;
	};
	return y;
};

uint64_t calculateBalancedCoinFlips(const uint64_t& number)
{
	/*
		Give a number of coin flips (number), calculates the number of permutations
		of that many coin-flips that will result in an equal number of heads and
		tails outcomes.
	*/

	double n = (double)number;
	double y = factorial(n / 2.0);
	double z = factorial(n);
	return (z / (y * y));
};

double binomial_coefficient(const double& n, const double& k)
{
	double a = factorial(n);
	double b = factorial(k) * factorial(n - k);
	return (a / b);
};

void coinFlipDistribution(const uint64_t& n)
{
	for (uint64_t i = 0; i <= n; i++)
	{
		std::cout << std::to_string(binomial_coefficient((double)n, (double)i) / pow(2.0, (double)n)) << "\n";
	};
};

double calculateProbabilityOfHeads(const uint64_t& number)
{
	double n = (double)number;
	double p = 0.0;
	double q = 0.0;
	double k = 0.0;
	double sum = 0.0;

	for (uint64_t i = 0; i <= number; i++)
	{
		k = (double)i;
		p = binomial_coefficient(n, k) / pow(2.0, n);
		q = (k / n);
		sum += (p * q);
	};

	return sum;
};

int main()
{
	/*
	CoinFlipCounter counter;
	for (uint64_t i = 0; i < 1000000; i++)
	{
		counter.add(coinFlip());
	};

	std::cout << counter.toString() << "\n";
	*/

	/*
	for (uint64_t i = 1; i <= 5; i++)
	{
		uint64_t j = (uint64_t)pow(2.0, (double)i);
		std::cout << std::to_string(j) << " coin flips results in " << std::to_string(calculateBalancedCoinFlips(j)) << " balanced permutations.\n";
	};
	*/

	/*
	std::cout << "Odds \n";
	std::cout << std::to_string(binomial_coefficient(4, 0) / pow(2.0, 4.0)) << "\n";
	std::cout << std::to_string(binomial_coefficient(4, 1) / pow(2.0, 4.0)) << "\n";
	std::cout << std::to_string(binomial_coefficient(4, 2) / pow(2.0, 4.0)) << "\n";
	std::cout << std::to_string(binomial_coefficient(4, 3) / pow(2.0, 4.0)) << "\n";
	std::cout << std::to_string(binomial_coefficient(4, 4) / pow(2.0, 4.0)) << "\n";
	*/

	// coinFlipDistribution(4);

	// All this math, just to find out a coin flip is still 50:50 :P
	std::cout << "P(heads):" << std::to_string(calculateProbabilityOfHeads(8)) << "\n";

	std::cout << "Press [ENTER] to exit the program.\n";
	std::cin.get();
	return 0;
};