#include "2024_08.h"

namespace Day08_2024
{
	Point::Point(int x /* = 0 */, int y /* = 0 */)
	:	x(x), y(y)
	{
	}
	
	bool Point::operator < (const Point& rhs) const
	{
		return (y == rhs.y) ? x < rhs.x : y < rhs.y;
	}

	Antennas::Antennas(const vector<string>& input)
	{
		_width = (int)input[0].size();
		_height = (int)input.size();

		for (int y = 0; y < _height; y++)
			for (int x = 0; x < _width; x++)
				if (input[y][x] != '.')
					_map[input[y][x]].push_back(Point(x, y));
	}

	bool Antennas::add(int x, int y)
	{
		if (x < 0 || x >= _width || y < 0 || y >= _height)
			return false;

		_output.insert(Point(x, y));
		return true;
	}

	void Antennas::add(int x, int y, int dx, int dy)
	{
		add(x, y);
		while (1)
		{
			x += dx;
			y += dy;
			if (!add(x, y))
				break;
		}
	}

	size_t Antennas::part_one()
	{
		for (const auto& [_, pts] : _map)
		{
			for (size_t i = 0; i < pts.size(); i++)
				for (size_t j = 0; j < pts.size(); j++)
					if (i != j)
					{
						const auto& p1 = pts[i];
						const auto& p2 = pts[j];
						int dx = p1.x - p2.x;
						int dy = p1.y - p2.y;
						if (p1.x - dx != p2.x && p1.y - dy != p2.y)
							add(p1.x - dx, p1.y - dy);

						if (p1.x + dx != p2.x && p1.y + dy != p2.y)
							add(p1.x + dx, p1.y + dy);
					}
		}

		return _output.size();
	}

	size_t Antennas::part_two()
	{
		for (const auto& [_, pts] : _map)
		{
			for (size_t i = 0; i < pts.size(); i++)
				for (size_t j = i + 1; j < pts.size(); j++)
				{
					int p1x = pts[i].x;
					int p2x = pts[j].x;
					int p1y = pts[i].y;
					int p2y = pts[j].y;
					if (p1x > p2x)
					{
						add(p1x, p1y, p1x - p2x, p1y - p2y);
						add(p2x, p2y, p2x - p1x, p2y - p1y);
					}
					else
					{
						add(p2x, p2y, p2x - p1x, p2y - p1y);
						add(p1x, p1y, p1x - p2x, p1y - p2y);
					}
				}
		}

		return _output.size();
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		return Antennas(input).part_one();
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		return Antennas(input).part_two();
	}
}
