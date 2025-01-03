#include "2023_21.h"

// explained here:
// https://github.com/tbielak/AoC_cpp/blob/master/doc/2023_21.md

namespace Day21_2023
{
	bool Main::assumptions_fulfilled(const vector<string>& input)
	{
		// checking the most important assumptions on which solution is based
		for (const auto& s : input)
			if (s.size() != 131)
				return false;

		if (input.size() != 131)
			return false;

		if (input[65][65] != 'S')
			return false;

		for (int i = 0; i < 131; i++)
			if (input[65][i] == '#' || input[i][65] == '#' ||
				input[0][i] == '#' || input[130][i] == '#' || input[i][0] == '#' || input[i][130] == '#')
				return true;

		return true;
	}
	
	t_points Main::starting_point()
	{
		t_points points;
		points.insert(make_pair(65, 65));
		return points;
	}

	t_points Main::step(const vector<string>& input, const t_points& points)
	{
		static vector<int> move_x = { 0, 1, 0, -1 };
		static vector<int> move_y = { 1, 0, -1, 0 };

		t_points output;
		int size = (int)input.size();
		for (const auto& [px, py] : points)
		{
			for (int i = 0; i < 4; i++)
			{
				int x = px + move_x[i];
				int y = py + move_y[i];
				if (input[(y + size * 1000) % size][(x + size * 1000) % size] != '#')
					output.insert(make_pair(x, y));
			}
		}

		return output;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		if (!assumptions_fulfilled(input))
			return -1;	// no solution

		auto points = starting_point();
		for (int i = 0; i < 64; i++)
			points = step(input, points);

		return points.size();
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		if (!assumptions_fulfilled(input))
			return -1;	// no solution

		auto points = starting_point();
		
		int k = 2;
		int size = (int)input.size();
		for (int i = 0; i < k * size + size / 2; i++)
			points = step(input, points);

		map<pair<int, int>, int64_t> count;
		for (int y = -k; y <= k; y++)
			for (int x = -k; x <= k; x++)
			{
				int minx = x * size;
				int maxx = minx + size;
				int miny = y * size;
				int maxy = miny + size;

				int64_t c = 0;
				for (const auto& [x, y] : points)
					if (x >= minx && x < maxx && y >= miny && y < maxy)
						c++;

				count[make_pair(x, y)] = c;
			}

		k = 26501365 / size;
		return count[make_pair(-2, 0)] + count[make_pair(0, -2)] + count[make_pair(0, 2)] + count[make_pair(2, 0)] +
			(count[make_pair(-2, -1)] + count[make_pair(1, -2)] + count[make_pair(-1, 2)] + count[make_pair(1, 2)]) * k +
			(count[make_pair(-1, -1)] + count[make_pair(1, -1)] + count[make_pair(-1, 1)] + count[make_pair(1, 1)]) * (k - 1) +
			count[make_pair(0, 0)] * (k - 1) * (k - 1) +
			count[make_pair(0, 1)] * k * k;
	}
}
