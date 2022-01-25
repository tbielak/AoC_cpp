#include "2015_01.h"

namespace Day01_2015
{
	AoC::Output Main::part_one(const string& input)
	{
		return (int)(count(input.begin(), input.end(), '(') - count(input.begin(), input.end(), ')'));
	}

	AoC::Output Main::part_two(const string& input)
	{
		int c = 0;
		for (size_t i = 0; i < input.size(); i++)
		{
			if ('(' == input[i]) c++;
			if (')' == input[i]) c--;
			if (-1 == c)
				return int(i) + 1;
		}

		return -1;
	}
}
