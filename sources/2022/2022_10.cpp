#include "2022_10.h"

namespace Day10_2022
{
	AoC::Output Main::both_parts(const vector<string>& input)
	{
		int current_cycle = 0;
		int stop_at_cycle = 20;
		int register_x = 1;
		int screen_x = 0;
		int screen_y = 0;
		vector<int> signal_strength;
		vector<string> screen = vector<string>(6, string(40, ' '));

		for (const string& s : input)
		{
			char instruction = s[0];
			int instruction_cycles = (instruction == 'a') ? 2 : 1;

			for (int c = 0; c < instruction_cycles; c++)
			{
				current_cycle++;
				if (current_cycle == stop_at_cycle)
				{
					signal_strength.push_back(current_cycle * register_x);
					stop_at_cycle += 40;
				}

				if (register_x - 1 == screen_x || register_x == screen_x || register_x + 1 == screen_x)
					screen[screen_y][screen_x] = -37;

				screen_x++;
				if (screen_x == 40)
				{
					screen_x = 0;
					screen_y++;
				}
			}

			if (instruction == 'a')
				register_x += stoi(s.substr(5));
		}

		vector<string> result;
		result.push_back(to_string(reduce(signal_strength.begin(), signal_strength.end())));
		result.insert(result.end(), screen.begin(), screen.end());
		return result;
	}
}
