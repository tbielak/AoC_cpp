#ifndef __2021_03__
#define __2021_03__

#include "../shared/Solution.h"

namespace Day03_2021
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static int find_rating(const vector<string>& x, int xor_mask);
	};
}

#endif
