#include "2022_04.h"

namespace Day04_2022
{
	vector<t_assignment> Main::load(const vector<string>& input)
	{
		vector<t_assignment> items;
		for (const auto& s : input)
		{
			stringstream ss(s);
			int min1, max1, min2, max2;
			ss >> min1;
			ss.ignore(1);
			ss >> max1;
			ss.ignore(1);
			ss >> min2;
			ss.ignore(1);
			ss >> max2;

			items.push_back(make_tuple(min1, max1, min2, max2));
		}

		return items;
	}

	bool Main::fully_containing(const t_assignment& x)
	{
		const auto& [min1, max1, min2, max2] = x;
		return ((min1 <= min2 && max1 >= max2) || (min2 <= min1 && max2 >= max1));
	}

	bool Main::overlapping(const t_assignment& x)
	{
		const auto& [min1, max1, min2, max2] = x;
		return (!((min1 < min2 && max1 < min2) || (min2 < min1 && max2 < min1)));
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto items = load(input);
		return count_if(items.begin(), items.end(), [](const auto& assignment) { return fully_containing(assignment); });
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto items = load(input);
		return count_if(items.begin(), items.end(), [](const auto& assignment) { return overlapping(assignment); });
	}
}
