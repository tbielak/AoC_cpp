#ifndef __2023_12__
#define __2023_12__

#include "../shared/Solution.h"

namespace Day12_2023
{
	using Area = vector<vector<vector<int64_t>>>;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static int64_t solve(Area& area, const string& s, vector<int> v, int i, int j, int c);
		static int64_t solve(const string& input, int rep);
		static int64_t solve(const vector<string>& input, int rep);
	};
}

#endif
