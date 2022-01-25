#ifndef __2016_13__
#define __2016_13__

#include "../shared/Solution.h"

namespace Day13_2016
{
	class Point
	{
	public:
		Point(int x, int y);
		bool operator < (const Point& rhs) const;
		bool operator == (const Point& rhs) const;

		int x, y;

		static vector<Point> next_position;
	};

	typedef map<Point, bool> t_visited;
	typedef set<Point> t_distinct;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output both_parts(const string& input);

	private:
		static int parity(int x);
		static bool can_go(const Point& p, int fav);
		static void walk(Point me, const Point& dst, t_visited& visited, int fav, int length, int& min_length, t_distinct& distinct, int steps);
	};
}

#endif
