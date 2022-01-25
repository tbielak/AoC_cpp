#include "2021_06.h"

namespace Day06_2021
{
	t_data Main::load(const string& input)
	{
		t_data x;
		int number;
		stringstream ss(input);
		while (ss >> number)
		{
			x.push_back(number);
			ss.ignore(1);
		}

		return x;
	}

	int64_t Main::number_of_elements(int x, int days)
	{
		vector<int64_t> count = vector<int64_t>(9, 0);
		count[x]++;

		int64_t v = 0;
		for (int d = 0; d < days; d++)
		{
			v = count[0];
			for (int i = 0; i < 8; i++)
				count[i] = count[i + 1];

			count[6] += v;
			count[8] = v;
		}

		int64_t sum = 0;
		for (auto n : count)
			sum += n;

		return sum;
	}

	int64_t Main::lanternfish_count(const t_data& x, int days)
	{
		int m = *max_element(x.begin(), x.end()) + 1;
		vector<int64_t> counts = vector<int64_t>(m);
		for (int i = 0; i < m; i++)
			counts[i] = number_of_elements(i, days);

		int64_t sum = 0;
		for (auto n : x)
			sum += counts[n];

		return sum;
	}

	AoC::Output Main::part_one(const string& input)
	{
		return lanternfish_count(load(input), 80);
	}

	AoC::Output Main::part_two(const string& input)
	{
		return lanternfish_count(load(input), 256);
	}
}
