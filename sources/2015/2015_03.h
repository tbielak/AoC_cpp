#ifndef __2015_03__
#define __2015_03__

#include "../shared/Solution.h"

namespace Day03_2015
{
	typedef set<pair<int, int>> t_visitedLocations;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);
	};
}

#endif
