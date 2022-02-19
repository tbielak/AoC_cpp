#ifndef __2017_03__
#define __2017_03__

#include "../shared/Solution.h"

namespace Day03_2017
{
	class Point
	{
	public:
		Point(int x = 0, int y = 0);
		bool operator < (const Point& rhs) const;

		int x, y;
	};

	typedef map<Point, int> t_spiral;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);

	private:
		static int iabs(int v);
		static int neighbours(const Point& p, const t_spiral& spiral);
	};
}

#endif
