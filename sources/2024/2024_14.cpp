#include "2024_14.h"

namespace Day14_2024
{
	Point::Point(int x, int y)
	:	x(x), y(y)
	{
	}

	bool Point::operator < (const Point& rhs) const
	{
		return (y == rhs.y) ? x < rhs.x : y < rhs.y;
	}

	vector<t_robot> Main::load(const vector<string>& input)
	{
		vector<t_robot> robots;
		smatch matches;
		regex regex("p=([-]*[0-9]+),([-]*[0-9]+) v=([-]*[0-9]+),([-]*[0-9]+)");
		for (const string& s : input)
		{
			regex_search(s, matches, regex);
			robots.push_back(make_pair(Point(stoi(matches[1]), stoi(matches[2])),
				Point(stoi(matches[3]), stoi(matches[4]))));
		}

		return robots;
	}

	int Main::sgn(int v)
	{
		return (0 < v) - (v < 0);
	}

	int Main::which_quadrant(const Point& p, int width, int height)
	{
		int sx = sgn(p.x - width / 2);
		int sy = sgn(p.y - height / 2);
		if (sx == 0 || sy == 0)
			return -1;

		return ((sx + 1) >> 1) + (sy + 1);
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto robots = load(input);
		vector<int> quadrant = { 0, 0, 0, 0 };
		const int width = 101;
		const int height = 103;
		const int seconds = 100;

		for (const auto& [p, v] : robots)
		{
			Point target((p.x + seconds * (v.x + width)) % width, (p.y + seconds * (v.y + height)) % height);
			int q = which_quadrant(target, width, height);
			if (q > -1)
				quadrant[q]++;
		}

		return quadrant[0] * quadrant[1] * quadrant[2] * quadrant[3];
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto robots = load(input);
		const int width = 101;
		const int height = 103;

		int c = 0;
		while (1)
		{
			c++;
			vector<string> bathroom = vector<string>(height, string(width, '.'));
			bool duplicated_positions = false;
			for (auto& [p, v] : robots)
			{
				p.x = (p.x + v.x + width) % width;
				p.y = (p.y + v.y + height) % height;
				if (bathroom[p.y][p.x] == '*')
					duplicated_positions = true;
				else
					bathroom[p.y][p.x] = '*';
			}

			if (!duplicated_positions)
				return c;
		}
	}
}
