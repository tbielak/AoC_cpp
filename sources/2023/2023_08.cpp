#include "2023_08.h"

namespace Day08_2023
{
	Data Main::load(const vector<string>& input)
	{
		Data data;
		data.directions = input[0];
		for (size_t i = 2; i < input.size(); i++)
			data.network[input[i].substr(0, 3)] =
				make_pair(input[i].substr(7, 3), input[i].substr(12, 3));

		return data;
	}

	int Main::solve(const Data& data, string node)
	{
		int idx = 0;
		int steps = 0;
		while (node[2] != 'Z')
		{
			char direction = data.directions[idx++];
			if (idx == (int)data.directions.size())
				idx = 0;

			auto& [left, right] = data.network.find(node)->second;
			node = (direction == 'L') ? left : right;
			steps++;
		}

		return steps;
	}

	int64_t Main::greatest_common_divisor(int64_t a, int64_t b)
	{
		while (b != 0)
		{
			int64_t x = b;
			b = a % b;
			a = x;
		}

		return a;
	}

	int64_t Main::least_common_multiple(int64_t a, int64_t b)
	{
		return a / greatest_common_divisor(a, b) * b;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return solve(load(input), "AAA");
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto data = load(input);

		int64_t steps = 1;
		for (const auto& [node, _] : data.network)
			if (node[2] == 'A')
				steps = least_common_multiple(steps, solve(data, node));

		return steps;
	}
}
