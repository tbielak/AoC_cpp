#include "2020_11.h"

namespace Day11_2020
{
	int adj(const t_input& grid, int y, int x)
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

	bool go(const t_input& grid, int y, int x, int ya, int xa)
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

	int see(const t_input& grid, int y, int x)
	{
		int c = 0;
		const vector<pair<int, int>> displ = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
		for (const auto& v : displ)
			if (go(grid, y, x, v.second, v.first))
				c++;

		return c;
	}

	int count(const t_input& grid)
	{
		int c = 0;
		for (const auto& s : grid)
			c += (int)count(s.begin(), s.end(), '#');

		return c;
	}

	int simulate(t_input s, int seats_count, int (*func)(const t_input&, int, int))
	{
		t_input t = s;
		while (1)
		{
			for (int x = 0; x < (int)s[0].size(); x++)
				for (int y = 0; y < (int)s.size(); y++)
				{
					if (s[y][x] == 'L' && func(s, y, x) == 0) t[y][x] = '#';
					if (s[y][x] == '#' && func(s, y, x) >= seats_count) t[y][x] = 'L';
				}

			if (s == t)
				return count(s);

			s = t;
		}

		return -1;
	}

	int part_one(const t_input& grid)
	{
		return simulate(grid, 4, adj);
	}

	int part_two(const t_input& grid)
	{
		return simulate(grid, 5, see);
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(input);
		auto p2 = part_two(input);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
