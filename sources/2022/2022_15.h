#ifndef __2022_15__
#define __2022_15__

#include "../shared/Solution.h"

namespace Day15_2022
{
	class Point
	{
	public:
		Point(int x, int y);
		bool operator < (const Point& rhs) const;

		int x, y;
	};

	class Range
	{
	public:
		Range(int start = INT_MAX, int end = INT_MIN);
		bool operator < (const Range& rhs) const;

		int start, end;
	};

	class Item
	{
	public:
		Item(const Point& sensor, const Point& beacon);

		Point sensor;
		Point beacon;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static vector<Item> load(const vector<string>& input);
		static int iabs(int x);
		static int distance(const Point& p1, const Point& p2);
	};
}

#endif
