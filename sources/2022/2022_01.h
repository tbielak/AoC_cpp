#ifndef __2022_01__
#define __2022_01__

#include "../shared/Solution.h"

namespace Day01_2022
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static int total_calories(const vector<string>& input, size_t top_count = 1);
	};
}

#endif
