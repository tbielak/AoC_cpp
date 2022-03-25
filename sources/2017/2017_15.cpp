#include "2017_15.h"

namespace Day15_2017
{
	int Main::solve(const vector<string>& input, int loops, int mod_a, int mod_b)
	{
		int64_t a = 0;
		int64_t b = 0;

		smatch matches;
		regex regex("Generator (A|B) starts with ([0-9]*)");
		for (const auto& line : input)
		{
			regex_search(line, matches, regex);
			if (matches[1] == 'A')
				a = stoi(matches[2]);
			if (matches[1] == 'B')
				b = stoi(matches[2]);
		}

		int count = 0;
		for (int i = 0; i < loops; i++)
		{
			do a = (a * 16807) % 2147483647; while ((a % mod_a) > 0);
			do b = (b * 48271) % 2147483647; while ((b % mod_b) > 0);
			if ((a & 0xffff) == (b & 0xffff))
				count++;
		}

		return count;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return solve(input, 40000000, 1, 1);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return solve(input, 5000000, 4, 8);
	}
}
