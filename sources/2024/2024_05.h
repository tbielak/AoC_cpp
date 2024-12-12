#ifndef __2024_05__
#define __2024_05__

#include "../shared/Solution.h"

namespace Day05_2024
{
	typedef vector<vector<int>> t_updates;
	typedef map<int, set<int>> t_predecessors;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static pair<t_updates, t_predecessors> load(const vector<string>& input);
		static bool ordered(const vector<int>& pages, const t_predecessors& predecessors);
		static vector<int> fixed_order(const vector<int>& pages, const t_predecessors& predecessors);
	};
}

#endif
