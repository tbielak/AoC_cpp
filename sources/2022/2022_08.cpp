#include "2022_08.h"

namespace Day08_2022
{
	AoC::Output Main::both_parts(const vector<string>& input)
	{
		const vector<int> move_x = { -1, 1, 0, 0 };
		const vector<int> move_y = { 0, 0, -1, 1 };

		int height = (int)input.size();
		int width = (int)input[0].size();
		int highest_scenic_score = 0;
		int visible_count = width * 2 + (height - 2) * 2;

		for (int cy = 1; cy < height - 1; cy++)
			for (int cx = 1; cx < height - 1; cx++)
			{
				int me = input[cy][cx];
				bool any_direction_visible = false;
				int scenic_score = 1;
				for (int i = 0; i < 4; i++)
				{
					int distance = 0;
					int x = cx + move_x[i];
					int y = cy + move_y[i];
					bool one_direction_visible = true;
					while (x >= 0 && x < width && y >= 0 && y < height)
					{
						distance++;
						if (input[y][x] >= me)
						{
							one_direction_visible = false;
							break;
						}

						x += move_x[i];
						y += move_y[i];
					}

					any_direction_visible |= one_direction_visible;
					scenic_score *= distance;
				}

				if (any_direction_visible)
					visible_count++;

				highest_scenic_score = max(scenic_score, highest_scenic_score);
			}

		return make_pair(visible_count, highest_scenic_score);
	}
}
