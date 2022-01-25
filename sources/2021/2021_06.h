#ifndef __2021_06__
#define __2021_06__

#include "../shared/Solution.h"

namespace Day06_2021
{
	typedef vector<int> t_data;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);

	private:
		static t_data load(const string& input);
		static int64_t number_of_elements(int x, int days);
		static int64_t lanternfish_count(const t_data& x, int days);
	};
}

#endif
