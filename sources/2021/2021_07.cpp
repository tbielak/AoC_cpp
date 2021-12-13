#include "2021_07.h"

namespace Day07_2021
{
	int iabs(int v)
	{
		return (v < 0) ? -v : v;
	}

	template<typename Functor>
	int calculate_fuel(const vector<int>& x, Functor ftor)
	{
		int m = *max_element(x.begin(), x.end());

		int min_fuel = INT_MAX;
		for (int i = 1; i <= m; i++)
		{
			int fuel = accumulate(x.begin(), x.end(), 0, [ftor, i](int x, int v) { return x + ftor(iabs(v - i)); });
			min_fuel = min(min_fuel, fuel);
		}

		return min_fuel;
	}

	int part_one(const vector<int>& x)
	{
		return calculate_fuel(x, [](auto distance) -> int { return distance; });
	}

	int part_two(const vector<int>& x)
	{
		return calculate_fuel(x, [](auto distance) -> int { return (distance * (distance + 1)) / 2; });
	}

	t_output main(const t_input& input)
	{
		vector<int> x;
		int number;
		stringstream ss(input[0]);
		while (ss >> number)
		{
			x.push_back(number);
			ss.ignore(1);
		}

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
