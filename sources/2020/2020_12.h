#ifndef __2020_12__
#define __2020_12__

#include "../shared/Solution.h"

namespace Day12_2020
{
	typedef pair<char, int> t_instruction;
	typedef vector<t_instruction> t_navigation;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_navigation load(const vector<string>& input);
	};
}

#endif
