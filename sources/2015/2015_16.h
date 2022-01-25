#ifndef __2015_16__
#define __2015_16__

#include "../shared/Solution.h"

namespace Day16_2015
{
	typedef vector<int> t_vecint;
	typedef vector<vector<int>> t_vec2int;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_vec2int load(const vector<string>& input);
	};
}

#endif
