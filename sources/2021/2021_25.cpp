#include "2021_25.h"

namespace Day25_2021
{
	int part_one(t_input sea)
	{
		// sea size
		int height = (int)sea.size();
		int width = (int)sea[0].size();

		int step = 0;
		while (1)
		{
			// next step
			step++;
			
			// remember current sea to check later if it changed
			t_input before = sea;

			// create new empty sea (with '.' everywhere)
			t_input new_sea(height, string(width, '.'));
			
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

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(input);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
