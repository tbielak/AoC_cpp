#include "2022_01.h"

namespace Day01_2022
{
	int Main::total_calories(const vector<string>& input, size_t top_count /* = 1 */)
	{
		vector<int> elfs;
		int calories = 0;
		for (const auto& line : input)
		{
			if (line.empty())
			{
				elfs.push_back(calories);
				calories = 0;
			}
			else
				calories += stoi(line);
		}

		elfs.push_back(calories);
		sort(elfs.begin(), elfs.end(), greater<int>());

		calories = 0;
		for (size_t i = 0; i < top_count; i++)
			calories += elfs[i];

		return calories;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return total_calories(input);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return total_calories(input, 3);
	}
}
