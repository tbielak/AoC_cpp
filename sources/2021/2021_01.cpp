#include "2021_01.h"

namespace Day01_2021
{
	t_data Main::load(const vector<string>& input)
	{
		t_data x;
		for (const auto& line : input)
			x.push_back(stoi(line));

		return x;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto x = load(input);

		int c = 0;
		for (size_t i = 1; i < x.size(); i++)
			if (x[i] > x[i - 1])
				c++;

		return c;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto x = load(input);

		int c = 0;
		for (size_t i = 3; i < x.size(); i++)
			if (x[i] + x[i - 1] + x[i - 2] > x[i - 1] + x[i - 2] + x[i - 3])
				c++;

		return c;
	}
}
