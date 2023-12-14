#ifndef __2023_03__
#define __2023_03__

#include "../shared/Solution.h"

namespace Day03_2023
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static bool adjacent_to_symbol(const vector<string>& input, int y, int x, int xr);
		static bool read_number(vector<int>& v, const vector<string>& input, int y, int x);
	};
}

#endif
