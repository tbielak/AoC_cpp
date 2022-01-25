#include "2020_11.h"

namespace Day11_2020
{
	int Main::adj(const vector<string>& grid, int y, int x)
	{
		int c = 0;
		if (y > 0)
		{
			if (x > 0 && grid[y - 1][x - 1] == '#') c++;
			if (grid[y - 1][x] == '#') c++;
			if (x < (int)grid[0].size() - 1 && grid[y - 1][x + 1] == '#') c++;
		}

		if (x > 0 && grid[y][x - 1] == '#') c++;
		if (x < (int)grid[0].size() - 1 && grid[y][x + 1] == '#') c++;

		if (y < (int)grid.size() - 1)
		{
			if (x > 0 && grid[y + 1][x - 1] == '#') c++;
			if (grid[y + 1][x] == '#') c++;
			if (x < (int)grid[0].size() - 1 && grid[y + 1][x + 1] == '#') c++;
		}

		return c;
	}

	bool Main::go(const vector<string>& grid, int y, int x, int ya, int xa)
	{
		while (1)
		{
			y += ya;
			x += xa;
			if (y == -1 || y == (int)grid.size() || x == -1 || x == (int)grid[0].size())
				break;

			if (grid[y][x] == 'L')
				break;

			if (grid[y][x] == '#')
				return true;
		}

		return false;
	}

	int Main::see(const vector<string>& grid, int y, int x)
	{
		int c = 0;
		const vector<pair<int, int>> displ = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
		for (const auto& v : displ)
			if (go(grid, y, x, v.second, v.first))
				c++;

		return c;
	}

	int Main::count_them(const vector<string>& grid)
	{
		int c = 0;
		for (const auto& s : grid)
			c += (int)count(s.begin(), s.end(), '#');

		return c;
	}

	int Main::simulate(vector<string> s, int seats_count, int (*func)(const vector<string>&, int, int))
	{
		vector<string> t = s;
		while (1)
		{
			for (int x = 0; x < (int)s[0].size(); x++)
				for (int y = 0; y < (int)s.size(); y++)
				{
					if (s[y][x] == 'L' && func(s, y, x) == 0) t[y][x] = '#';
					if (s[y][x] == '#' && func(s, y, x) >= seats_count) t[y][x] = 'L';
				}

			if (s == t)
				return count_them(s);

			s = t;
		}

		return -1;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return simulate(input, 4, adj);
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return simulate(input, 5, see);
	}
}
