#ifndef __2017_19__
#define __2017_19__

#include "../shared/Solution.h"

namespace Day19_2017
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output both_parts(const vector<string>& input);

	private:
		static int path(const vector<string>& input, int y, int x, int c);
	};
}

#endif
