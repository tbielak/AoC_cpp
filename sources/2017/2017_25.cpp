#include "2017_25.h"

namespace Day25_2017
{
	AoC::Output Main::part_one(const vector<string>& input)
	{
		size_t i = 3;
		t_actions actions;
		while (i < input.size())
		{
			char state = input[i++][9];
			while (1)
			{
				int value = input[i++][26] - '0';
				actions[state].target_value[value] = input[i++][22] - '0';
				actions[state].move[value] = input[i++][27] == 'r' ? 1 : -1;
				actions[state].goto_state[value] = input[i++][26];
				if (i == input.size() || input[i].size() == 0)
					break;
			}

			i++;
		}

		t_tape tape;
		tape[0] = 0;
		int pos = 0;
		char state = input[0][15];
		int steps = stoi(input[1].substr(36));

		for (int i = 0; i < steps; i++)
		{
			int value = tape[pos];
			tape[pos] = actions[state].target_value[value];
			pos += actions[state].move[value];
			state = actions[state].goto_state[value];
		}

		return accumulate(tape.begin(), tape.end(), 0, [](int sum, const auto& v) { return sum + v.second; });
	}
}
