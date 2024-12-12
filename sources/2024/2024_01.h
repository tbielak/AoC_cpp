#ifndef __2024_01__
#define __2024_01__

#include "../shared/Solution.h"

namespace Day01_2024
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static int iabs(int i);
	};
}

#endif
