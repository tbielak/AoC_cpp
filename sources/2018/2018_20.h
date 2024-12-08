#ifndef __2018_20__
#define __2018_20__

#include "../shared/Solution.h"

namespace Day20_2018
{
	class Position
	{
	public:
		Position(int x = 0, int y = 0);
		bool operator < (const Position& rhs) const;

		int x, y;
	};

	class Node
	{
	public:
		Position pos;
		int dist = 0;
	};

	typedef map<Position, int> t_distances;

	class Solver
	{
	public:
		Solver(const string& input);

		int longest_path() const;
		int at_least(int threshold) const;

	private:
		Node _current;
		t_distances _distances;

		void move(int dx, int dy);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);
	};
}

#endif
