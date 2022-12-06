#ifndef __2022_03__
#define __2022_03__

#include "../shared/Solution.h"

namespace Day03_2022
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static int priority(char c);
	};
}

#endif
