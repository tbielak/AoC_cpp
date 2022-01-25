#ifndef __2016_01__
#define __2016_01__

#include "../shared/Solution.h"

namespace Day01_2016
{
	class Command
	{
	public:
		Command(int direction, int steps);

		int direction;	// -1 (left) or 1 (right)
		int steps;
	};

	typedef vector<Command> t_route;

	class Point
	{
	public:
		Point(int x, int y);
		bool operator < (const Point& rhs) const;
		int distance() const;

		int x, y;
		static const vector<Point> update_position;
	};

	typedef set<Point> t_visited;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);

	private:
		static t_route load(const string& input);
	};
}

#endif
