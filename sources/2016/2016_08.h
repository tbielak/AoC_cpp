#ifndef __2016_08__
#define __2016_08__

#include "../shared/input_output.h"

namespace Day08_2016
{
	struct Command
	{
		char id;	// r = rotate row, c = rotate column, f = fill rect
		int p1;		// param1 = which row/column on rotate; width when rect
		int p2;		// param2 = how many shifts on rotate; height when rect
	};

	typedef vector<Command> t_commands;

	t_output main(const t_input& input);
}

#endif
