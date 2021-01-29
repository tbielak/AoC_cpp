#include "2015_03.h"

namespace Day03_2015
{
	int part_one(const string& s)
	{
		int x = 0;
		int y = 0;
		t_visitedLocations visited;
		visited.insert(make_pair(x, y));

		for (auto c : s)
		{
			if ('^' == c) y--;
			if ('v' == c) y++;
			if ('>' == c) x--;
			if ('<' == c) x++;
			visited.insert(make_pair(x, y));
		}

		return (int)visited.size();
	}

	int part_two(const string& s)
	{
		int x[2] = { 0, 0 };
		int y[2] = { 0, 0 };
		t_visitedLocations visited;
		visited.insert(make_pair(x[0], y[0]));

		int i = 0;
		for (auto c : s)
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

	t_output main(const t_input& input)
	{
		string line = input[0];

		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(line);
		auto p2 = part_two(line);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
