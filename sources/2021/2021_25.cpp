#include "2021_25.h"

namespace Day25_2021
{
	AoC::Output Main::part_one(const vector<string>& input)
	{
		// sea
		t_sea sea = input;
		int height = (int)sea.size();
		int width = (int)sea[0].size();

		int step = 0;
		while (1)
		{
			// next step
			step++;
			
			// remember current sea to check later if it changed
			t_sea before = sea;

			// create new empty sea (with '.' everywhere)
			t_sea new_sea(height, string(width, '.'));
			
			// set '>' in new sea in their new positions
			for (int y = 0; y < height; y++)
				for (int x = 0; x < width; x++)
				{
					if (sea[y][x] == '>')
					{
						int n = (x + 1) % width;
						if (sea[y][n] == '.')
							new_sea[y][n] = '>';
						else
							new_sea[y][x] = '>';
					}
				}

			// update positions of '>' in sea
			for (int y = 0; y < height; y++)
				for (int x = 0; x < width; x++)
				{
					// free old positions
					if (sea[y][x] == '>')
						sea[y][x] = '.';

					// put them in new positions
					if (new_sea[y][x] == '>')
						sea[y][x] = '>';
				}

			// set 'v' in new sea in their new positions
			for (int y = 0; y < height; y++)
				for (int x = 0; x < width; x++)
				{
					if (sea[y][x] == 'v')
					{
						int n = (y + 1) % height;
						if (sea[n][x] == '.')
							new_sea[n][x] = 'v';
						else
							new_sea[y][x] = 'v';
					}
				}

			// new sea becomes current sea
			sea = new_sea;

			// not changed? -> solved
			if (before == sea)
				return step;
		}

		return -1;
	}
}
