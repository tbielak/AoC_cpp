#ifndef __2016_13__
#define __2016_13__

#include "../shared/input_output.h"

namespace Day13_2016
{
	class Point
	{
	public:
		Point(int x, int y);
		bool operator < (const Point& rhs) const;
		bool operator == (const Point& rhs) const;

		int x, y;
	};

	typedef map<Point, bool> t_visited;
	typedef set<Point> t_distinct;

	t_output main(const t_input& input);
}

#endif
