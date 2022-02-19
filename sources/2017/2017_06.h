#ifndef __2017_06__
#define __2017_06__

#include "../shared/Solution.h"

namespace Day06_2017
{
	typedef vector<int> t_data;
	typedef set<t_data> t_known;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);

	private:
		t_data _observe;

		static t_data load(const string& input);
		static pair<int, t_data> solve(const string& input, const t_data& observe = t_data());
	};
}

#endif
