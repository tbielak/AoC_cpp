#ifndef __2015_02__
#define __2015_02__

#include "../shared/Solution.h"

namespace Day02_2015
{
	typedef vector<tuple<int, int, int>> t_items;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_items load(const vector<string>& input);
	};
}

#endif
