#ifndef __2021_22__
#define __2021_22__

#include "../shared/input_output.h"

namespace Day22_2021
{
	class Cuboid
	{
	public:
		Cuboid(int x1, int x2, int y1, int y2, int z1, int z2);

		int x1, x2, y1, y2, z1, z2;
	};

	typedef vector<pair<Cuboid, char>> t_cubes;

	t_output main(const t_input& input);
}

#endif
