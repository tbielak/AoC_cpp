#ifndef __2023_16__
#define __2023_16__

#include "../shared/Solution.h"

namespace Day16_2023
{
	class Point
	{
	public:
		Point(int y, int x);
		
		bool operator < (const Point& rhs) const;
		bool operator == (const Point& rhs) const;
		
		int y, x;
	};

	class Beam
	{
	public:
		Beam(const Point& p, int h);

		bool operator < (const Beam& rhs) const;

		Point p;
		int h;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static size_t solve(const vector<string>& input, const Beam& b);
	};
}

#endif
