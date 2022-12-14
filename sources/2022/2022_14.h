#ifndef __2022_14__
#define __2022_14__

#include "../shared/Solution.h"

namespace Day14_2022
{
	class Point
	{
	public:
		Point(int x = 0, int y = 0);
		Point(const string& s);
		bool operator < (const Point& rhs) const;
		bool empty() const;

		int x, y;
	};

	typedef set<Point> t_points;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static tuple<t_points, int> load(const vector<string>& input);
		static bool free_fall(const set<Point>& data, Point& p, int floor);
	};
}

#endif
