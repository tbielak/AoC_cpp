#ifndef __2021_22__
#define __2021_22__

#include "../shared/Solution.h"

namespace Day22_2021
{
	class Cuboid
	{
	public:
		Cuboid(int x1, int x2, int y1, int y2, int z1, int z2);

		int x1, x2, y1, y2, z1, z2;
	};

	typedef vector<pair<Cuboid, char>> t_cubes;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_cubes load(const vector<string>& input);

		template<typename Functor>
		int64_t solve(const t_cubes& cubes, Functor include) const;
	};
}

#endif
