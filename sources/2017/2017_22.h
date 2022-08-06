#ifndef __2017_22__
#define __2017_22__

#include "../shared/Solution.h"

namespace Day22_2017
{
	class Position
	{
	public:
		Position(int x = 0, int y = 0);
		bool operator < (const Position& rhs) const;

		int x, y;
	};

	// map: position-to-infection status
	// infection status: clean = 0, weakened = 1, infected = 2, flagged = 3
	typedef map<Position, int> t_infection_map;

	class Grid
	{
	public:
		Grid(const vector<string>& input);
		int burst(int part, int steps);

	private:
		t_infection_map _map;
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		int count(const string& input, int size, int add);
	};
}

#endif
