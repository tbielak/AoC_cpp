#ifndef __2021_11__
#define __2021_11__

#include "../shared/input_output.h"

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
		Octopuses(const t_input& input);

		int flashes_after(int steps);
		int all_flashed();

	private:
		t_input _grid;
		int _size;

		int step();
		void increase_energy(t_vecPosition& pos, t_setPosition& flash, const Position& p);
		bool inside(int y, int x);
	};

	t_output main(const t_input& input);
}

#endif
