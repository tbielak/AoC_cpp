#ifndef __2017_01__
#define __2017_01__

#include "../shared/Solution.h"

namespace Day01_2017
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);

	private:
		int count(const string& input, int size, int add);
	};
}

#endif
