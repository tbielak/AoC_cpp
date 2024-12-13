#ifndef __2024_07__
#define __2024_07__

#include "../shared/Solution.h"

namespace Day07_2024
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static int64_t solve(const string& s, const string& ops_defined);
	};
}

#endif
