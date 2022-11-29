#ifndef __2017_11__
#define __2017_11__

#include "../shared/Solution.h"

namespace Day11_2017
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output both_parts(const string& input);

	private:
		static int iabs(int v);
		static int distance(int x, int y);
	};
}

#endif
