#ifndef __2016_08__
#define __2016_08__

#include "../shared/Solution.h"

namespace Day08_2016
{
	struct Command
	{
		char id;	// r = rotate row, c = rotate column, f = fill rect
		int p1;		// param1 = which row/column on rotate; width when rect
		int p2;		// param2 = how many shifts on rotate; height when rect
	};

	typedef vector<Command> t_commands;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output both_parts(const vector<string>& input);

	private:
		static t_commands load(const vector<string>& input);
	};
}

#endif
