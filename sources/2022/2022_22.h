#ifndef __2022_22__
#define __2022_22__

#include "../shared/Solution.h"

namespace Day22_2022
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static tuple<int, int, int> control_cube_edges(int x, int y, int facing);
		static bool solvable(const vector<string>& board);
		static int solve(const vector<string>& input, bool flat);
	};
}

#endif
