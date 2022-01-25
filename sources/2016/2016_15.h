#ifndef __2016_15__
#define __2016_15__

#include "../shared/Solution.h"

namespace Day15_2016
{
    typedef vector<pair<int, int>> t_discs;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_discs load(const vector<string>& input);
		static int solve(const t_discs& discs);
	};
}

#endif
