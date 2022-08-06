#ifndef __2017_23__
#define __2017_23__

#include "../shared/Solution.h"

namespace Day23_2017
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
		virtual AoC::Output part_two(const vector<string>& input);

	private:
		vector<bool> sieveOfEratosthenes(int n);
	};
}

#endif
