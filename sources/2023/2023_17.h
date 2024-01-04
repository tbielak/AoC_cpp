#ifndef __2023_17__
#define __2023_17__

#include "../shared/Solution.h"

namespace Day17_2023
{
	class Point
	{
	public:
		Point(int y, int x);
		bool operator < (const Point& rhs) const;
		bool operator == (const Point& rhs) const;

		int y, x;
	};

	class State
	{
	public:
		State(const Point& p, int d, int c);
		bool operator < (const State& rhs) const;

		Point point;
		int direction, count;
	};

	class Distance
	{
	public:
		Distance(int v = INT_MAX);
		bool operator < (const Distance& rhs) const;
		bool operator > (const Distance& rhs) const;
		operator int() const;

	private:
		int value;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static vector<State> adjacent(const State& s, int cmin, int cmax);
		static map<State, Distance> dijkstra(const vector<string>& input, int cmin, int cmax, int height, int width);
		static int solve(const vector<string>& input, int cmin, int cmax);
	};
}

#endif
