#include "2015_20.h"

namespace Day20_2015
{
	int Main::lowest_house_number(int input, int presents, int houses_limit)
	{
		for (int reduce = 30; reduce > 0; reduce -= 5)		// 30 should be ok :-)
		{
			int limit = input / reduce;
			vector<int> x(limit);
			for (int i = 1; i < limit; i++)
			{
				int j = i;
				int h = 0;
				do
				{
					x[j] += i * presents;
					j += i;
					h++;
				} while (j < limit && h < houses_limit);
			}

			for (int i = 0; i < limit; i++)
				if (x[i] >= input)
					return i;
		}

		return -1;
	}

	AoC::Output Main::part_one(const string& input)
	{
		return lowest_house_number(stoi(input), 10, INT_MAX);
	}

	AoC::Output Main::part_two(const string& input)
	{
		return lowest_house_number(stoi(input), 11, 50);
	}
}
