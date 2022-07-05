#ifndef __2018_06__
#define __2018_06__

#include "../shared/Solution.h"

namespace Day06_2018
{
	class MinMax
	{
	public:
		MinMax();

		int min, max;
	};

	class Point
	{
	public:
		Point(int x, int y);

		int x, y;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static vector<Point> load(const vector<string>& input, MinMax& mx, MinMax& my);
		static int iabs(int x);
		static int Manhattan_distance(const Point& a, const Point& b);
		static int closest_point(const vector<Point>& points, const Point& p);
		static int count_fields(const vector<vector<int>>& area, const MinMax& mx, const MinMax& my, int which);
		int sum_distance(const vector<Point>& points, const Point& p);
	};
}

#endif
