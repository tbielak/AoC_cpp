#include "2023_10.h"

namespace Day10_2023
{
	bool Point::operator < (const Point& rhs) const
	{
		return (y == rhs.y) ? x < rhs.x : y < rhs.y;
	}

	pair<int, int> Main::starting_point(const vector<string>& input)
	{
		for (int y = 0; y < (int)input.size(); y++)
			for (int x = 0; x < (int)input[y].size(); x++)
				if (input[y][x] == 'S')
					return make_pair(x, y);

		return make_pair(-1, -1); // unreachable
	}

	Visited Main::solve(const vector<string>& input)
	{
		static vector<int> move_x{ 1, 0, -1, 0 };	// right=0, down=1, left=2, up=3
		static vector<int> move_y{ 0, 1, 0, -1 };	// right=0, down=1, left=2, up=3
		static string inchar = "LJF7";
		vector<vector<int>> target_orientation = { { 0, -1, 1, 0 }, { 3, 1, 0, 0 }, { 0, 0, -1, -3 }, { 1, 0, 0, -1 } };

		Visited visited;
		auto [bx, by] = starting_point(input);

		int x = bx;
		int y = by;
		int orientation = 1;	// assumption: going down in first step!

		do
		{
			auto idx = inchar.find_first_of(input[y][x]);
			if (idx != string::npos)
				orientation += target_orientation[idx][orientation];

			x += move_x[orientation];
			y += move_y[orientation];

			visited[{ y, x }] = input[y][x];
		}
		while (x != bx || y != by);

		return visited;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return solve(input).size() / 2;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto visited = solve(input);

		vector<string> clean_map = vector<string>(input.size(), string(input[0].size(), '.'));
		for (const auto& [p, c] : visited)
			clean_map[p.y][p.x] = c;

		int count = 0;
		for (const string& s : clean_map)
		{
			char b = 0;
			bool inside = false;
			for (char c : s)
			{
				if (c == '|')
					inside = !inside;

				if (c == '.' && inside)
					count++;

				if (b == 0)
				{
					if (c == 'F' || c == 'L')
						b = c;
				}
				else
				{
					if (c == 'J' || c == '7')
					{
						if ((b == 'F' && c == 'J') || (b == 'L' && c == '7'))
							inside = !inside;

						b = 0;
					}
				}
			}
		}

		return count;
	}
}
