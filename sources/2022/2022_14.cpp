#include "2022_14.h"

namespace Day14_2022
{
	Point::Point(int x /* = 0 */, int y /* = 0 */)
	:	x(x), y(y)
	{
	}

	Point::Point(const string& s)
	{
		size_t pos = s.find(",");
		x = stoi(s.substr(0, pos));
		y = stoi(s.substr(pos + 1));
	}

	bool Point::operator < (const Point& rhs) const
	{
		return (x == rhs.x) ? y < rhs.y : x < rhs.x;
	}
	
	bool Point::empty() const
	{
		return x == 0;
	}

	tuple<t_points, int> Main::load(const vector<string>& input)
	{
		t_points data;
		int y_max_global = 0;
		for (string s : input)
		{
			Point from, to;
			while (s.size() > 0)
			{
				Point p;
				size_t pos = s.find(" -> ");
				if (pos != string::npos)
				{
					p = Point(s.substr(0, pos));
					s = s.substr(pos + 4);
				}
				else
				{
					p = Point(s);
					s = "";
				}

				if (from.empty())
					from = p;
				else
				{
					to = p;
					if (from.x == to.x && from.y != to.y)
					{
						int y_min = min(from.y, to.y);
						int y_max = max(from.y, to.y);
						y_max_global = max(y_max_global, y_max);
						for (int y = y_min; y <= y_max; y++)
							data.insert(Point(from.x, y));
					}
					else
						if (from.x != to.x && from.y == to.y)
						{
							int x_min = min(from.x, to.x);
							int x_max = max(from.x, to.x);
							y_max_global = max(y_max_global, from.y);
							for (int x = x_min; x <= x_max; x++)
								data.insert(Point(x, from.y));
						}
						else
							throw;

					from = to;
				}
			}
		}

		return make_tuple(data, y_max_global);
	}

	bool Main::free_fall(const set<Point>& data, Point& p, int floor)
	{
		if (p.y == floor - 1)
			return false;

		bool free[3];
		for (int i = 0; i < 3; i++)
			free[i] = (data.find(Point(p.x + i - 1, p.y + 1)) == data.end());

		if (free[0] || free[1] || free[2])
		{
			p.y++;
			if (!free[1])
			{
				if (free[0])
					p.x--;
				else
					p.x++;
			}

			return true;
		}

		return false;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto [points, y_max] = load(input);

		int units = 0;
		while (1)
		{
			Point p(500, 0);
			while (1)
			{
				if (free_fall(points, p, y_max + 2))
				{
					if (p.y > y_max)
						return units;
				}
				else
				{
					units++;
					points.insert(p);
					break;
				}
			}
		}

		return -1;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto [points, y_max] = load(input);

		int units = 0;
		while (1)
		{
			Point p(500, 0);
			while (1)
			{
				if (!free_fall(points, p, y_max + 2))
				{
					units++;
					if (p.y == 0)
						return units;

					points.insert(p);
					break;
				}
			}
		}

		return -1;
	}
}
