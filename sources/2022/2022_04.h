#ifndef __2022_04__
#define __2022_04__

#include "../shared/Solution.h"

namespace Day04_2022
{
	typedef tuple<int, int, int, int> t_assignment;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		static vector<t_assignment> load(const vector<string>& input);
		static bool fully_containing(const t_assignment& x);
		static bool overlapping(const t_assignment& x);
	};
}

#endif
