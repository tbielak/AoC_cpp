#include "2020_01.h"

namespace Day01_2020
{
	int part_one(const vector<int>& x)
	{
		for (auto a : x)
			for (auto b : x)
				if (2020 == a + b)
					return  a * b;

		return -1;
	}

	int part_two(const vector<int>& x)
	{
		for (auto a : x)
			for (auto b : x)
				for (auto c : x)
					if (2020 == a + b + c)
						return  a * b * c;

		return -1;
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
