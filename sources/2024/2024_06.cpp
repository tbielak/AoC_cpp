#include "2024_06.h"

namespace Day06_2024
{
	vector<int> Main::_move_x = { 0, 1, 0, -1 };
	vector<int> Main::_move_y = { -1, 0, 1, 0 };

	pair<int, int> Main::starting_point(const vector<string>& input)
	{
		for (int y = 0; y < (int)input.size(); y++)
			for (int x = 0; x < (int)input[y].size(); x++)
				if (input[y][x] == '^')
					return make_pair(x, y);

		throw;
	}

	size_t Main::walk(const vector<string>& input, const pair<int, int>& sp)
	{
		int dir = 0;
		auto [x, y] = sp;
		set<pair<int, int>> visited;

		while (1)
		{
			visited.insert(make_pair(x, y));

			int nx = x + _move_x[dir];
			int ny = y + _move_y[dir];
			if (nx == -1 || nx == (int)input[0].size() || ny == -1 || ny == (int)input.size())
				return visited.size();

			if (input[ny][nx] == '#')
				dir = (dir + 1) & 3;
			else
			{
				x = nx;
				y = ny;
			}
		}
	}

	bool Main::loop(const vector<string>& input, int x, int y, int ox, int oy)
	{
		int dir = 0;
		size_t c = 0;
		size_t c_max = input[0].size() * input.size();

		while (1)
		{
			if (++c == c_max)
				return true;

			int nx = x + _move_x[dir];
			int ny = y + _move_y[dir];
			if (nx == -1 || nx == (int)input[0].size() || ny == -1 || ny == (int)input.size())
				return false;

			if (input[ny][nx] == '#' || (ny == oy && nx == ox))
				dir = (dir + 1) & 3;
			else
			{
				x = nx;
				y = ny;
			}
		}
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return walk(input, starting_point(input));
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto [sx, sy] = starting_point(input);

		int c = 0;
		for (int y = 0; y < (int)input.size(); y++)
			for (int x = 0; x < (int)input[y].size(); x++)
				if (input[y][x] == '.')
					if (loop(input, sx, sy, x, y))
						c++;

		return c;
	}
}
