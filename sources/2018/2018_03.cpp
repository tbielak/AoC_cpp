#include "2018_03.h"

namespace Day03_2018
{
	Point::Point(int x /* = 0 */, int y /* = 0 */)
	:	x(x), y(y)
	{
	}

	bool Point::operator < (const Point& rhs) const
	{
		return (x == rhs.x) ? y < rhs.y : x < rhs.x;
	}

	Fabric::Fabric()
	:	width(0), height(0)
	{
	}

	Fabric::Fabric(const Point& point, int width, int height)
	:	point(point), width(width), height(height)
	{
	}

	t_fabrics Main::load(const vector<string>& input)
	{
		t_fabrics fabrics;
		smatch matches;
		regex regex("#([0-9]*) @ ([0-9]*),([0-9]*): ([0-9]*)x([0-9]*)");
		for (const auto& s : input)
		{
			regex_search(s, matches, regex);
			fabrics[stoi(matches[1])] = Fabric(
				Point(stoi(matches[2]), stoi(matches[3])), stoi(matches[4]), stoi(matches[5]));
		}
		
		return fabrics;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		auto fabrics = load(input);

		map<Point, int> points;
		for (const auto& [id, f] : fabrics)
		{
			for (int x = f.point.x; x < f.point.x + f.width; x++)
				for (int y = f.point.y; y < f.point.y + f.height; y++)
					points[Point(x, y)]++;
		}
		
		return accumulate(points.begin(), points.end(), 0, [](int count, const auto& item) { return count + int(item.second > 1); });
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		auto fabrics = load(input);

		map<Point, set<int>> points;
		for (const auto& [id, f] : fabrics)
		{
			for (int x = f.point.x; x < f.point.x + f.width; x++)
				for (int y = f.point.y; y < f.point.y + f.height; y++)
					points[Point(x, y)].insert(id);
		}

		set<int> ids;
		for (const auto& [id, f] : fabrics)
			ids.insert(id);

		for (const auto& x : points)
			if (x.second.size() > 1)
			{
				for (const auto& id : x.second)
					ids.erase(id);
			}

		return *ids.begin();
	}
}
