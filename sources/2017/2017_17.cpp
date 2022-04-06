#include "2017_17.h"

namespace Day17_2017
{
	AoC::Output Main::part_one(const string& input)
	{
		int steps = stoi(input);

		int cp = 0;
		vector<int> state = { 0 };
		for (int i = 1; i <= 2017; i++)
		{
			int offs = int((steps % state.size() + cp) % state.size());
			state.insert(begin(state) + offs + 1, i);
			cp = offs + 1;
		}

		return state[(cp + 1) % state.size()];
	}

	AoC::Output Main::part_two(const string& input)
	{
		int steps = stoi(input);

		int value = 0;
		int cp = 0;
		for (int i = 1; i <= 50000000; i++)
		{
			cp = (cp + 1 + steps) % i;
			if (cp == 0)
				value = i;
		}

		return value;
	}
}
