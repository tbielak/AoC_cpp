#include "2019_01.h"

namespace Day01_2019
{
	int part_one(const vector<int>& x)
	{
		return accumulate(x.begin(), x.end(), 0, [](int sum, int v) { return sum + (v / 3) - 2; });
	}

	int part_two(const vector<int>& x)
	{
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
