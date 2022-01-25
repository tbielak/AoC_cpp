#ifndef __2021_09__
#define __2021_09__

#include "../shared/Solution.h"

namespace Day09_2021
{
	class Point
	{
	public:
		Point(int x, int y);
		bool operator == (const Point& rhs) const;

		int x, y;
	};

	typedef vector<Point> t_vecPoint;
	typedef vector<t_vecPoint> t_basins;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		t_basins load(const vector<string>& input);
		static void add_point(t_vecPoint& b, const Point& p);
	};
}

#endif
