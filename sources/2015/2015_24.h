#ifndef __2015_24__
#define __2015_24__

#include "../shared/Solution.h"

namespace Day24_2015
{
	typedef vector<int> t_vecint;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output both_parts(const vector<string>& input);

	private:
		static int fast_bit_count(int x);
		static int sum_group(const t_vecint& input, int group, int count);
		static int64_t QE(const t_vecint& input, int group, int count);
	};
}

#endif
