#ifndef __2016_18__
#define __2016_18__

#include "../shared/Solution.h"

namespace Day18_2016
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);

	private:
		static int count_safe(const string& input, int rows);
	};
}

#endif
