#include "2022_06.h"

namespace Day06_2022
{
	size_t Main::unique_position(const string& input, size_t distinct_chars)
	{
		size_t index = 0;
		while (1)
		{
			string s = input.substr(index, distinct_chars);
			if (set<char>(s.begin(), s.end()).size() == distinct_chars)
				break;

			index++;
		}

		return index + distinct_chars;
	}

	AoC::Output Main::part_one(const string& input)
	{
		return unique_position(input, 4);
	}

	AoC::Output Main::part_two(const string& input)
	{
		return unique_position(input, 14);
	}
}
