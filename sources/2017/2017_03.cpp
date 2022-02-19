#include "2017_03.h"

namespace Day03_2017
{
	Point::Point(int x /* = 0 */, int y /* = 0 */)
	:	x(x), y(y)
	{
	}

	bool Point::operator < (const Point& rhs) const
	{
		return (x == rhs.x) ? y < rhs.y : x < rhs.x;
	}

	vector<pair<int, int>> position_update = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };
	vector<int> count_update = { 0, 1, 0, 1 };

	int Main::iabs(int v)
	{
		return v < 0 ? -v : v;
	}

	AoC::Output Main::part_one(const string& input)
	{
		int x = 0;
		int y = 0;
		int value = 1;
		int count = 1;
		int target = stoi(input);

		while (1)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int i = 0; i < count; i++)
				{
					if (value == target)
						return iabs(x) + iabs(y);

					x += position_update[j].first;
					y += position_update[j].second;
					value++;
				}

				count += count_update[j];
			}
		}
		
		return -1;
	}

	int Main::neighbours(const Point& p, const t_spiral& spiral)
	{
		int sum = 0;
		for (int x = -1; x <= 1; x++)
			for (int y = -1; y <= 1; y++)
			{
				Point t = Point(p.x + x, p.y + y);
				t_spiral::const_iterator it = spiral.find(t);
				if (it != spiral.end())
					sum += it->second;
			}

		return sum;
	}

	AoC::Output Main::part_two(const string& input)
	{
		t_spiral spiral;
		int target = stoi(input);

		Point p;
		spiral[p] = 1;
		
		int count = 1;
		while (1)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int i = 0; i < count; i++)
				{
					int value = neighbours(p, spiral);
					if (value > target)
						return value;

					spiral[p] = value;
					p.x += position_update[j].first;
					p.y += position_update[j].second;
				}

				count += count_update[j];
			}
		}

		return -1;
	}
}
