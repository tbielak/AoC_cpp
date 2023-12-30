#ifndef __2023_10__
#define __2023_10__

#include "../shared/Solution.h"

namespace Day10_2023
{
	class Point
	{
	public:
		bool operator < (const Point& rhs) const;

		int y, x;
	};

	using Visited = map<Point, char>;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static pair<int, int> starting_point(const vector<string>& input);
		static Visited solve(const vector<string>& input);
	};
}

#endif
