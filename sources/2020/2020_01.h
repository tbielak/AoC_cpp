#ifndef __2020_01__
#define __2020_01__

#include "../shared/Solution.h"

namespace Day01_2020
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
