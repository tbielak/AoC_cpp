#include "2021_09.h"

namespace Day09_2021
{
	Point::Point(int x, int y)
	:	x(x), y(y)
	{
	}
		
	bool Point::operator == (const Point& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	t_basins Main::load(const vector<string>& input)
	{
		t_basins basins;
		
		int height = (int)input.size();
		int width = (int)input[0].size();

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if ((x == 0 || (x > 0 && input[y][x] < input[y][x - 1])) &&
					(x == width - 1 || (x < width - 1 && input[y][x] < input[y][x + 1])) &&
					(y == 0 || (y > 0 && input[y][x] < input[y - 1][x])) &&
					(y == height - 1 || (y < height - 1 && input[y][x] < input[y + 1][x])))
				{
					// low point found
					basins.push_back(t_vecPoint());
					basins.back().push_back(Point(x, y));
				}
			}
		}

		return basins;
	}

	void Main::add_point(t_vecPoint& b, const Point& p)
	{
		// performance note:
		// linear find = not optimal, but fast enough for this task

		if (find(b.begin(), b.end(), p) == b.end())
			b.push_back(p);
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto basins = load(input);
		
		int risk_level = 0;
		for (const auto& b : basins)
			for (const auto& p : b)
				risk_level += ((input[p.y][p.x] - '0') + 1);

		return risk_level;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		int height = (int)input.size();
		int width = (int)input[0].size();

		auto basins = load(input);
		for (auto& b : basins)
		{
			size_t i = 0;
			while (i < b.size())
			{
				int x = b[i].x;
				int y = b[i].y;

				if ((x > 0) && (input[y][x] < input[y][x - 1]) && (input[y][x - 1] != '9'))
					add_point(b, Point(x - 1, y));

				if ((x < width - 1) && (input[y][x] < input[y][x + 1]) && (input[y][x + 1] != '9'))
					add_point(b, Point(x + 1, y));

				if ((y > 0) && (input[y][x] < input[y - 1][x]) && (input[y - 1][x] != '9'))
					add_point(b, Point(x, y - 1));

				if ((y < height - 1) && (input[y][x] < input[y + 1][x]) && (input[y + 1][x] != '9'))
					add_point(b, Point(x, y + 1));

				i++;
			}
		}

		vector<size_t> v;
		for (const auto& b : basins)
			v.push_back(b.size());

		sort(v.begin(), v.end());
		return int(v[v.size() - 1] * v[v.size() - 2] * v[v.size() - 3]);
	}
}
