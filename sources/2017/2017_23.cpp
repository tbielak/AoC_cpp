#include "2017_23.h"

namespace Day23_2017
{
	vector<bool> Main::sieveOfEratosthenes(int n)
	{
		vector<bool> sieve = vector<bool>(n + 1, true);
		for (int i = 2; i * i <= n; i++)
			if (sieve[i])
				for (int j = i * i; j <= n; j += i)
					sieve[j] = false;

		return sieve;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		int b = stoi(input[0].substr(6));
		return (b - 2) * (b - 2);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		int b = stoi(input[0].substr(6)) * 100 + 100000;
		int c = b + 17000;
		auto sieve = sieveOfEratosthenes(c);

		int h = 0;
		for (; b <= c; b += 17)
			if (!sieve[b])
				h++;

		return h;
	}
}
