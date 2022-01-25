#include "2019_01.h"

namespace Day01_2019
{
	t_data Main::load(const vector<string>& input)
	{
		t_data data;
		for (const auto& line : input)
			data.push_back(stoi(line));

		return data;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		t_data x = load(input);
		return accumulate(x.begin(), x.end(), 0, [](int sum, int v) { return sum + (v / 3) - 2; });
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		t_data x = load(input);

		int sum = 0;
		for (auto v : x)
		{
			while (v > 0)
			{
				v = max((v / 3) - 2, 0);
				sum += v;
			}
		}

		return sum;
	}
}
