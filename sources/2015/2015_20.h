#ifndef __2015_20__
#define __2015_20__

#include "../shared/Solution.h"

namespace Day20_2015
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);

	private:
		static int lowest_house_number(int input, int presents, int houses_limit);
	};
}

#endif
