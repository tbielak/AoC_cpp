#ifndef __2023_13__
#define __2023_13__

#include "../shared/Solution.h"

namespace Day13_2023
{
	using Pattern = vector<string>;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static vector<Pattern> load(const vector<string>& input);
		static Pattern rotate(const Pattern& src);
		static bool check_diffs(const Pattern& p, int k, int smudges);
		static int find_reflection(const Pattern& p, int smudges);
		static int solve(const vector<string>& input, int smudges);
	};
}

#endif
