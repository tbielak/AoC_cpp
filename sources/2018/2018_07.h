#ifndef __2018_07__
#define __2018_07__

#include "../shared/Solution.h"

namespace Day07_2018
{
	typedef set<char> t_setchar;
	typedef map<char, t_setchar> t_graph;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_graph load(const vector<string>& input);
	};
}

#endif
