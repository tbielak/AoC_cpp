#ifndef __2022_05__
#define __2022_05__

#include "../shared/Solution.h"

namespace Day05_2022
{
	typedef map<int, string> t_stacks;
	typedef vector<tuple<int, int, int>> t_moves;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static tuple<t_stacks, t_moves> load(const vector<string>& input);
		static string print(const t_stacks& stacks);
	};
}

#endif
