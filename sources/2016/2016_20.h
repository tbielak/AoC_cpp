#ifndef __2016_20__
#define __2016_20__

#include "../shared/Solution.h"

namespace Day20_2016
{
	typedef pair<uint32_t, uint32_t> t_range;   // range <min, max>
	typedef vector<t_range> t_vecrange;         // vector of ranges

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static void block(t_vecrange& white_list, const t_range& range);
		static t_vecrange load(const vector<string>& input);
	};
}

#endif
