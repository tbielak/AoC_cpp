#include "2017_01.h"

namespace Day01_2017
{
	int Main::count(const string& input, int size, int add)
	{
		int sum = 0;
		for (int i = 0; i < size; i++)
		{
			int j = (i + add) % size;
			if (input[i] == input[j])
				sum += input[i] - '0';
		}

		return sum;
	}

	AoC::Output Main::part_one(const string& input)
	{
		return count(input, (int)input.size(), 1);
	}

	AoC::Output Main::part_two(const string& input)
	{
		return count(input, (int)input.size(), (int)input.size() / 2);
	}
}
