#ifndef __2017_02__
#define __2017_02__

#include "../shared/Solution.h"

typedef vector<vector<int>> t_data;

namespace Day02_2017
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_data load(const vector<string>& input);
	};
}

#endif
