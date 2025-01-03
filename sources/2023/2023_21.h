#ifndef __2023_21__
#define __2023_21__

#include "../shared/Solution.h"

namespace Day21_2023
{
	typedef set<pair<int, int>> t_points;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static bool assumptions_fulfilled(const vector<string>& input);
		static t_points starting_point();
		static t_points step(const vector<string>& input, const t_points& points);
	};
}

#endif
