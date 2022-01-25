#ifndef __2021_11__
#define __2021_11__

#include "../shared/Solution.h"

namespace Day11_2021
{
	class Position
	{
	public:
		Position(int y, int x);
		bool operator < (const Position& rhs) const;

		int y, x;
	};

	typedef vector<Position> t_vecPosition;
	typedef set<Position> t_setPosition;

	class Octopuses
	{
	public:
		Octopuses(const vector<string>& input);

		int flashes_after(int steps);
		int all_flashed();

	private:
		vector<string> _grid;
		int _size;

		int step();
		void increase_energy(t_vecPosition& pos, t_setPosition& flash, const Position& p);
		bool inside(int y, int x);
	};

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);
	};
}

#endif
