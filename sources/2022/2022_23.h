#ifndef __2022_23__
#define __2022_23__

#include "../shared/Solution.h"

namespace Day23_2022
{
	class Point
	{
	public:
		Point(int x = INT_MIN, int y = INT_MIN);
		bool operator < (const Point& rhs) const;
		bool valid() const;

		int x, y;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output both_parts(const vector<string>& input);

	private:
		static bool any_elf_in_adjacent_eight(const set<Point>& pts, const Point& p);
		static Point propose_move(int cycle, const set<Point>& pts, const Point& p);
	};
}

#endif
