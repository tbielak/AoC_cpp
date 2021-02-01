#include "2015_20.h"

namespace Day20_2015
{
	int lowest_house_number(int input, int presents, int houses_limit)
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

	int part_one(int input)
	{
		return lowest_house_number(input, 10, INT_MAX);
	}

	int part_two(int input)
	{
		return lowest_house_number(input, 11, 50);
	}

	t_output main(const t_input& input)
	{
		int presents = stoi(input[0]);
		
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(presents);
		auto p2 = part_two(presents);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
