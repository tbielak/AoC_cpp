#include "2018_06.h"

namespace Day06_2018
{
	MinMax::MinMax()
		: min(INT_MAX), max(-1)
	{
	}

	Point::Point(int x, int y)
		: x(x), y(y)
	{
	}

	vector<Point> Main::load(const vector<string>& input, MinMax& mx, MinMax& my)
	{
		vector<Point> points;
		for (const auto& s : input)
		{
			size_t comma = s.find(',');
			int x = stoi(s.substr(0, comma));
			int y = stoi(s.substr(comma + 2));
			points.push_back(Point(x, y));

			mx.min = min(mx.min, x);
			mx.max = max(mx.max, x);
			my.min = min(my.min, y);
			my.max = max(my.max, y);
		}

		return points;
	}

	int Main::iabs(int x)
	{
		return (x < 0) ? -x : x;
	}

	int Main::Manhattan_distance(const Point& a, const Point& b)
	{
		return iabs(a.x - b.x) + iabs(a.y - b.y);
	}

	int Main::closest_point(const vector<Point>& points, const Point& p)
	{
		vector<pair<int, int>> mdist = vector<pair<int, int>>(points.size());
		for (int i = 0; i < (int)points.size(); i++)
			mdist[i] = make_pair(Manhattan_distance(points[i], p), i);

		sort(mdist.begin(), mdist.end());
		return (mdist[0].first == mdist[1].first ? -1 : mdist[0].second);
	}

	int Main::count_fields(const vector<vector<int>>& area, const MinMax& mx, const MinMax& my, int which)
	{
		int v = 0;
		for (int y = my.min; y <= my.max; y++)
			for (int x = mx.min; x <= mx.max; x++)
				if (area[y][x] == which)
					v++;

		return v;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		MinMax mx, my;
		auto points = load(input, mx, my);

		// finite area
		vector<vector<int>> area = vector<vector<int>>(my.max + 1, vector<int>(mx.max + 1, -1));

		// find closest point to every relevant point in the whole area
		for (int y = my.min; y <= my.max; y++)
			for (int x = mx.min; x <= mx.max; x++)
				area[y][x] = closest_point(points, Point(x, y));

		// find infinite points
		set<int> infinite;

		// in first and last row
		for (int x = mx.min; x <= mx.max; x++)
		{
			infinite.insert(area[my.min][x]);
			infinite.insert(area[my.max][x]);
		}

		// in first and last column
		for (int y = my.min; y <= my.max; y++)
		{
			infinite.insert(area[y][mx.min]);
			infinite.insert(area[y][mx.max]);
		}

		// count fields skipping infinite points
		vector<int> count = vector<int>(points.size(), 0);
		for (int i = 0; i < (int)points.size(); i++)
			count[i] = (infinite.find(i) != infinite.end()) ? -1 : count_fields(area, mx, my, i);

		// find largest area
		int largest = count[0];
		for (int i = 1; i < (int)points.size(); i++)
			largest = max(largest, count[i]);

		return largest;
	}

	int Main::sum_distance(const vector<Point>& points, const Point& p)
	{
		int sum = 0;
		for (const auto& pt : points)
			sum += Manhattan_distance(pt, p);

		return sum;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		MinMax mx, my;
		auto points = load(input, mx, my);

		int count = 0;
		for (int y = my.min; y <= my.max; y++)
			for (int x = mx.min; x <= mx.max; x++)
				if (sum_distance(points, Point(x, y)) < 10000)
					count++;

		return count;
	}
}
