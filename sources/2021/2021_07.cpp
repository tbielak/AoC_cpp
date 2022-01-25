#include "2021_07.h"

namespace Day07_2021
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

	int Main::iabs(int v) const
	{
		return (v < 0) ? -v : v;
	}

	template<typename Functor>
	int Main::calculate_fuel(const t_data& x, Functor ftor) const
	{
		int m = *max_element(x.begin(), x.end());

		int min_fuel = INT_MAX;
		for (int i = 1; i <= m; i++)
		{
			int fuel = accumulate(x.begin(), x.end(), 0, [this, ftor, i](int x, int v) { return x + ftor(iabs(v - i)); });
			min_fuel = min(min_fuel, fuel);
		}

		return min_fuel;
	}

	AoC::Output Main::part_one(const string& input)
	{
		return calculate_fuel(load(input), [](auto distance) -> int { return distance; });
	}

	AoC::Output Main::part_two(const string& input)
	{
		return calculate_fuel(load(input), [](auto distance) -> int { return (distance * (distance + 1)) / 2; });
	}
}
