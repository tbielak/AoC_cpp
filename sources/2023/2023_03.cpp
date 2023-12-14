#include "2023_03.h"

namespace Day03_2023
{
	bool Main::adjacent_to_symbol(const vector<string>& input, int y, int x, int xr)
	{
		for (int yy = y - 1; yy <= y + 1; yy++)
			for (int xx = x - 1; xx <= xr + 1; xx++)
				if (yy >= 0 && yy < (int)input.size() && xx >= 0 && xx < (int)input[y].size() &&
					input[yy][xx] != '.' && (!isdigit(input[yy][xx])))
						return true;

		return false;
	}

	bool Main::read_number(vector<int>& v, const vector<string>& input, int y, int x)
	{
		if (y < 0 || y >= (int)input.size() || x < 0 || x >= (int)input[y].size() ||
			!isdigit(input[y][x]))
			return false;

		while (x > 0 && isdigit(input[y][x])) x--;
		if (!isdigit(input[y][x])) x++;

		v.push_back(stoi(input[y].substr(x)));
		return true;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		int sum = 0;
		for (int y = 0; y < (int)input.size(); y++)
			for (int x = 0; x < (int)input[y].size(); x++)
				if (isdigit(input[y][x]))
				{
					int xr = x;
					while (xr < (int)input[y].size() && isdigit(input[y][xr])) xr++;
					if (xr < (int)input[y].size() && !isdigit(input[y][xr])) xr--;
					if (adjacent_to_symbol(input, y, x, xr))
						sum += stoi(input[y].substr(x, xr - x + 1));

					x = xr;
				}

		return sum;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		int sum = 0;
		for (int y = 0; y < (int)input.size(); y++)
			for (int x = 0; x < (int)input[y].size(); x++)
				if (input[y][x] == '*')
				{
					vector<int> v;
					if (!read_number(v, input, y - 1, x))
					{
						read_number(v, input, y - 1, x - 1);
						read_number(v, input, y - 1, x + 1);
					}

					read_number(v, input, y, x - 1);
					read_number(v, input, y, x + 1);

					if (!read_number(v, input, y + 1, x))
					{
						read_number(v, input, y + 1, x - 1);
						read_number(v, input, y + 1, x + 1);
					}

					if (v.size() == 2)
						sum += v[0] * v[1];
				}

		return sum;
	}
}
