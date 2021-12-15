#ifndef __2021_09__
#define __2021_09__

#include "../shared/input_output.h"

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

	t_output main(const t_input& input);
}

#endif
