#ifndef __2024_10__
#define __2024_10__

#include "../shared/Solution.h"

namespace Day10_2024
{
	class Point
	{
	public:
		Point(int x = 0, int y = 0);
		bool operator < (const Point& rhs) const;
		
		int x, y;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static int ratings(const vector<string>& input, const Point& start, bool distinct);
		static int solve(const vector<string>& input, bool distinct);
	};
}

#endif
