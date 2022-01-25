#ifndef __2019_16__
#define __2019_16__

#include "../shared/Solution.h"

namespace Day16_2019
{
	typedef vector<int> t_vecInt;
	typedef vector<t_vecInt> t_vecInt2;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const string& input);
		virtual AoC::Output part_two(const string& input);

	private:
		static int iabs(int x);
	};
}

#endif
