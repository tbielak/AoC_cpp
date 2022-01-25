#ifndef __2015_04__
#define __2015_04__

#include "../shared/Solution.h"

namespace Day04_2015
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);

	private:
		static int solve(int part, const string& line);
	};
}

#endif
