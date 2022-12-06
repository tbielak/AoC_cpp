#include "2022_02.h"

namespace Day02_2022
{
	AoC::Output Main::part_one(const vector<string>& input)
	{
		int score = 0;
		for (const auto& s : input)
		{
			// 1 = rock, 2 = paper, 3 = scissors
			int op = int(s[0] - 'A') + 1;
			int me = int(s[2] - 'X') + 1;

			if (op == me)
				score += me + 3;
			else
				score += me + (((me == 1 && op == 3) || (me == 3 && op == 2) || (me == 2 && op == 1)) ? 6 : 0);
		}

		return score;
	}

	AoC::Output Main::part_two(const vector<string>& input)
	{
		int score = 0;
		for (const auto& s : input)
		{
			// 1 = rock, 2 = paper, 3 = scissors
			int op = int(s[0] - 'A') + 1;
			int me = int(s[2] - 'X') + 1;

			if (me == 2)
				score += op + 3;
			else
				score += ((op + (me % 3)) % 3) + (me - 1) * 3 + 1;
		}

		return score;
	}
}
