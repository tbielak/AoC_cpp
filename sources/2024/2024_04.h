#ifndef __2024_04__
#define __2024_04__

#include "../shared/Solution.h"

namespace Day04_2024
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static int count(const vector<string>& input, int yy, int xx);
		static bool box_is_x(const vector<string>& input, int y, int x);
	};
}

#endif
