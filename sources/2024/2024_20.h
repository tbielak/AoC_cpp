#ifndef __2024_20__
#define __2024_20__

#include "../shared/Solution.h"

namespace Day20_2024
{
	class Point
	{
	public:
		Point(int x, int y);
		bool operator < (const Point& rhs) const;
		bool operator == (const Point& rhs) const;
		
		int x, y;
	};

	class Racetrack
	{
	public:
		Racetrack(const vector<string>& input);
		
		int cheat_count(int cheat_length, int requested_saving) const;

	private:
		vector<Point> _path;
		map<Point, int> _points;

		int iabs(int x) const;
		int manhattan_distance(const Point& a, const Point& b) const;
		int step(const Point& p) const;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
