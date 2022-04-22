#include "2018_01.h"

namespace Day01_2018
{
	AoC::Output Main::part_one(const vector<string>& input)
	{
		return accumulate(input.begin(), input.end(), 0, [](int freq, const auto& f) { return freq + stoi(f); });
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		set<int> known;
		int freq = 0;

		while (1)
		{
			for (const auto& f : input)
			{
				freq += stoi(f);
				if (known.find(freq) != known.end())
					return freq;

				known.insert(freq);
			}
		}

		return -1;	// unreachable code
	}
}
