#ifndef __2016_17__
#define __2016_17__

#include "../shared/Solution.h"

namespace Day17_2016
{
	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output both_parts(const string& input);

	private:
		static void go(int x, int y, const string& input, string path, string& shortest_path, string& longest_path);
	};
}

#endif
