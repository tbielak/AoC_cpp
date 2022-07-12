#include "2017_19.h"

namespace Day19_2017
{
	int Main::path(const vector<string>& input, int y, int x, int c)
	{
		return (input[y][x] == c || (input[y][x] >= 'A' && input[y][x] <= 'Z')) ? -1 : 1;
	}

	AoC::Output Main::both_parts(const vector<string>& input)
	{
		int y = 0;
		int x = 0;
		while (input[y][x] != '|') x++;

		int yadd = 1;
		int xadd = 0;
		int steps = 0;
		string output;

		while (1)
		{
			char c = input[y][x];
			if (c == ' ')
				break;

			if (c >= 'A' && c <= 'Z')
				output += c;
			else
			if (c == '+')
			{
				if (xadd == 0)
				{
					yadd = 0;
					xadd = path(input, y, x - 1, '-');
				}
				else
				{
					xadd = 0;
					yadd = path(input, y - 1, x, '|');
				}
			}

			y += yadd;
			x += xadd;
			steps++;
		}

		return make_pair(output, to_string(steps));
	}
}
