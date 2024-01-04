#ifndef __2023_14__
#define __2023_14__

#include "../shared/Solution.h"

namespace Day14_2023
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static void up(vector<string>& m, size_t y, size_t x);
		static bool move_north(vector<string>& m);
		static void tilt(vector<string>& m);
		static size_t sum(const vector<string>& m);
	};
}

#endif
