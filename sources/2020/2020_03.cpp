#include "2020_03.h"

namespace Day03_2020
{
	AoC::Output Main::part_one(const vector<string>& input)
	{
		int x = 0;
		int c = 0;
		int width = (int)input[0].size();
		for (const auto& s : input)
		{
			if (s[x] == '#') c++;
			x = (x + 3) % width;
		}

		return c;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		const vector<pair<int, int>> slopes = { {1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2} };

		int64_t m = 1;
		int width = (int)input[0].size();
		int height = (int)input.size();
		for (const auto& s : slopes)
		{
			int x = 0;
			int y = 0;
			int c = 0;
			do
			{
				if (input[y][x] == '#') c++;
				x += s.first;
				y += s.second;
				x %= width;
			} while (y < height);

			m *= c;
		}

		return m;
	}
}
