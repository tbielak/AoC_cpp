#ifndef __2017_05__
#define __2017_05__

#include "../shared/Solution.h"

namespace Day05_2017
{
	typedef vector<int> t_data;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_data load(const vector<string>& input);
		static int count(const vector<string>& input, bool always_add);
	};
}

#endif
