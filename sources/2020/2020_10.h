#ifndef __2020_10__
#define __2020_10__

#include "../shared/Solution.h"

namespace Day10_2020
{
	typedef vector<int> t_data;

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
