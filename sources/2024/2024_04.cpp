// REF
#include "2024_04.h"

namespace Day04_2024
{
	int count(const vector<string>& input, int yy, int xx)
	{
		int c = 0;
		for (int my = -1; my <= 1; my++)
			for (int mx = -1; mx <= 1; mx++)
			{
				if (my == 0 && mx == 0)
					continue;

				const string key = "MAS";
				int x = xx;
				int y = yy;
				for (int i = 0; i < (int)key.size(); i++)
				{
					x += mx;
					y += my;
					if (y < 0 || y > (int)input.size() - 1 || x < 0 || x > (int)input[y].size() - 1)
						break;

					if (input[y][x] != key[i])
						break;

					if (i == (int)key.size() - 1)
						c++;
				}
			}

		return c;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		int c = 0;
		for (int y = 0; y < (int)input.size(); y++)
			for (int x = 0; x < (int)input[y].size(); x++)
				if (input[y][x] == 'X')
					c += count(input, y, x);

		return c;
	}

	bool box_is_x(const vector<string>& input, int y, int x)
	{
		if (input[y][x] != 'A')
			return false;

		for (int my = -1; my <= 1; my++)
			for (int mx = -1; mx <= 1; mx++)
			{
				if (my == 0 && mx == 0)
					continue;

				if (input[y - my][x - my] == 'M' && input[y + my][x + my] == 'S')
				{
					if (input[y + my][x - my] == 'M' && input[y - my][x + my] == 'S')
						return true;

					if (input[y + my][x - my] == 'S' && input[y - my][x + my] == 'M')
						return true;
				}
			}

		return false;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		int c = 0;
		for (int y = 0; y < (int)input.size() - 2; y++)
			for (int x = 0; x < (int)input[y].size() - 2; x++)
				if (box_is_x(input, y + 1, x + 1))
					c++;

		return c;
	}
}
