#ifndef __2016_03__
#define __2016_03__

#include "../shared/Solution.h"

namespace Day03_2016
{
	typedef vector<vector<int>> t_data;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static t_data load(const vector<string>& input);
		static bool is_triangle(vector<int> x);
	};
}

#endif
