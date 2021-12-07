#include "2021_01.h"

namespace Day01_2021
{
	int part_one(const vector<int>& x)
	{
		int c = 0;
		for (size_t i = 1; i < x.size(); i++)
			if (x[i] > x[i - 1])
				c++;

		return c;
	}

	int part_two(const vector<int>& x)
	{
		int c = 0;
		for (size_t i = 3; i < x.size(); i++)
			if (x[i] + x[i - 1] + x[i - 2] > x[i - 1] + x[i - 2] + x[i - 3])
				c++;

		return c;
	}

	t_output main(const t_input& input)
	{
		vector<int> x;
		for (const auto& line : input)
			x.push_back(stoi(line));

		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(x);
		auto p2 = part_two(x);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
