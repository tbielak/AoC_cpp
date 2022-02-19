#include "2017_05.h"

namespace Day05_2017
{
	typedef vector<int> t_data;

	t_data Main::load(const vector<string>& input)
	{
		t_data data;
		for (const auto& s : input)
			data.push_back(stoi(s));

		return data;
	}

	int Main::count(const vector<string>& input, bool always_add)
	{
		auto data = load(input);

		int idx = 0;
		int steps = 0;
		while (1)
		{
			steps++;
			int v = data[idx];

			if (always_add || v < 3)
				data[idx]++;
			else
				data[idx]--;

			idx += v;
			if (idx < 0 || idx >= (int)data.size())
				break;
		}

		return steps;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return count(input, true);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return count(input, false);
	}
}
