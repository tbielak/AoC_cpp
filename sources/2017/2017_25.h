#ifndef __2017_25__
#define __2017_25__

#include "../shared/Solution.h"

namespace Day25_2017
{
	class Action
	{
	public:
		int target_value[2];
		int move[2];
		char goto_state[2];
	};

	typedef map<char, Action> t_actions;
	typedef map<int, int> t_tape;

	class Main : public AoC::Solution
	{
	public:
		virtual AoC::Output part_one(const vector<string>& input);
	};
}

#endif
