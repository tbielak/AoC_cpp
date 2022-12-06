#include "2022_03.h"

namespace Day03_2022
{
	int Main::priority(char c)
	{
		return (c >= 'a') ? int(c - 'a') + 1 : int(c - 'A') + 27;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		int sum = 0;
		for (const auto& s : input)
		{
			string r1 = s.substr(0, s.size() / 2);
			string r2 = s.substr(s.size() / 2);
			set<char> s1(r1.begin(), r1.end());
			set<char> s2(r2.begin(), r2.end());
			
			vector<char> intersection;
			set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(intersection));
			sum += priority(intersection[0]);
		}

		return sum;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		int sum = 0;
		for (size_t i = 0; i < input.size();)
		{
			map<char, int> contents;
			for (int j = 0; j < 3; j++)
				for (auto c : input[i++])
					contents[c] |= (1 << j);

			for (const auto& it : contents)
				if (it.second == 7)
				{
					sum += priority(it.first);
					break;
				}

		}

		return sum;
	}
}
