#ifndef __2024_14__
#define __2024_14__

#include "../shared/Solution.h"

namespace Day14_2024
{
	class Point
	{
	public:
		Point(int x, int y);
		bool operator < (const Point& rhs) const;

		int x, y;
	};

	typedef pair<Point, Point> t_robot;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static vector<t_robot> load(const vector<string>& input);
		static int sgn(int v);
		static int which_quadrant(const Point& p, int width, int height);
	};
}

#endif
