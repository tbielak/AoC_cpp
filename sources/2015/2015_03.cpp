#include "2015_03.h"

namespace Day03_2015
{
	AoC::Output Main::part_one(const string& input)
	{
		int x = 0;
		int y = 0;
		t_visitedLocations visited;
		visited.insert(make_pair(x, y));

		for (auto c : input)
		{
			if ('^' == c) y--;
			if ('v' == c) y++;
			if ('>' == c) x--;
			if ('<' == c) x++;
			visited.insert(make_pair(x, y));
		}

		return (int)visited.size();
	}

	AoC::Output Main::part_two(const string& input)
	{
		int x[2] = { 0, 0 };
		int y[2] = { 0, 0 };
		t_visitedLocations visited;
		visited.insert(make_pair(x[0], y[0]));

		int i = 0;
		for (auto c : input)
		{
			if ('^' == c) y[i]--;
			if ('v' == c) y[i]++;
			if ('>' == c) x[i]--;
			if ('<' == c) x[i]++;
			visited.insert(make_pair(x[i], y[i]));
			i ^= 1;
		}

		return (int)visited.size();
	}
}
