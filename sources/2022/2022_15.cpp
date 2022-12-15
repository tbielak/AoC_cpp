#include "2022_15.h"

namespace Day15_2022
{
	Point::Point(int x, int y)
	:	x(x), y(y)
	{
	}

	bool Point::operator < (const Point& rhs) const
	{
		return (x == rhs.x) ? y < rhs.y : x < rhs.x;
	}

	Range::Range(int start /* = INT_MAX */, int end /* = INT_MIN */)
	:	start(start), end(end)
	{
	}

	bool Range::operator < (const Range& rhs) const
	{
		return (start == rhs.start) ? end < rhs.end : start < rhs.start;
	}

	Item::Item(const Point& sensor, const Point& beacon)
	:	sensor(sensor), beacon(beacon)
	{
	}

	vector<Item> Main::load(const vector<string>& input)
	{
		smatch matches;
		regex regex("Sensor at x=([-0-9]*), y=([-0-9]*): closest beacon is at x=([-0-9]*), y=([-0-9]*)");
		vector<Item> items;
		for (const auto& line : input)
		{
			regex_search(line, matches, regex);
			items.push_back(Item(Point(stoi(matches[1].str()), stoi(matches[2].str())),
				Point(stoi(matches[3].str()), stoi(matches[4].str()))));
		}

		return items;
	}

	int Main::iabs(int x)
	{
		return x < 0 ? -x : x;
	}

	int Main::distance(const Point& p1, const Point& p2)
	{
		return iabs(p1.x - p2.x) + iabs(p1.y - p2.y);
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		const int line = 2000000;
		auto items = load(input);

		Range range;
		for (const auto& i : items)
		{
			int dist = distance(i.sensor, i.beacon);
			int diff = dist - distance(i.sensor, Point(i.sensor.x, line));
			int start = i.sensor.x - diff;
			int end = i.sensor.x + diff;
			if (start > end)
				continue;
			
			range.start = min(range.start, start);
			range.end = max(range.end, end);
		}

		return range.end - range.start;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		const int y_max = 4000000;
		auto items = load(input);

		int y = 0;
		while (1)
		{
			set<Range> ranges;
			for (const auto& i : items)
			{
				int dist = distance(i.sensor, i.beacon);
				int diff = dist - distance(i.sensor, Point(i.sensor.x, y));
				int start = i.sensor.x - diff;
				int end = i.sensor.x + diff;
				if (start > end)
					continue;

				start = max(0, start);
				end = min(y_max, end);
				ranges.insert(Range(start, end));
			}

			int x = 0;
			for (const auto& r : ranges)
			{
				if (x < r.start)
					return int64_t(x + 1) * y_max + int64_t(y);
				
				x = max(x, r.end);
			}

			y++;
		}

		return -1;
	}
}
