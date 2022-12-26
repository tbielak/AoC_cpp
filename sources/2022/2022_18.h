#ifndef __2022_18__
#define __2022_18__

#include "../shared/Solution.h"

namespace Day18_2022
{
	class Point
	{
	public:
		Point(int x, int y, int z);
		bool operator < (const Point& rhs) const;

		int x, y, z;
	};

	typedef set<Point> t_points;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_points load(const vector<string>& input);
	};
}

#endif
