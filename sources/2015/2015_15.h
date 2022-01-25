#ifndef __2015_15__
#define __2015_15__

#include "../shared/Solution.h"

namespace Day15_2015
{
	typedef vector<int> t_vecint;
	typedef vector<vector<int>> t_vec2int;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output both_parts(const vector<string>& input);

	private:
		static t_vec2int load(const vector<string>& input);
	};
}

#endif
