#include "2018_11.h"

namespace Day11_2018
{
	Grid::Grid(const string& serial_number)
	{
		int sn = stoi(serial_number);
		_grid = vector<vector<int>>(300, vector<int>(300));

		for (int y = 1; y <= 300; y++)
			for (int x = 1; x <= 300; x++)
			{
				int rack_id = x + 10;
				_grid[y - 1][x - 1] = ((((rack_id * y + sn) * rack_id) / 100) % 10) - 5;
			}
	}

	string Grid::solve(int smin, int smax) const
	{
		int lp = INT_MIN;
		int rx = 0;
		int ry = 0;
		int rs = 0;
		for (int s = smin; s <= smax; s++)
			for (int y = 0; y < 300 - s - 1; y++)
				for (int x = 0; x < 300 - s - 1; x++)
				{
					int p = 0;
					for (int ty = 0; ty < s; ty++)
						for (int tx = 0; tx < s; tx++)
							p += _grid[y + ty][x + tx];

					if (p > lp)
					{
						lp = p;
						rx = x;
						ry = y;
						rs = s;
					}
				}

		if (smin == smax)
			return to_string(rx + 1) + "," + to_string(ry + 1);

		return to_string(rx + 1) + "," + to_string(ry + 1) + "," + to_string(rs);
	}

	AoC::Output Main::part_one(const string& input)
	{
		return Grid(input).solve(3, 3);
	}

	AoC::Output Main::part_two(const string& input)
	{
		return Grid(input).solve(3, 300);
	}
}
