#include "2015_15.h"

namespace Day15_2015
{
	t_vecint solve(const t_vec2int& input)
	{
		const int total_amount = 100;
		const int req_calories = 500;

		t_vecint result(2);
		t_vecint amount(input.size());
		bool blocked = false;
		for (int part = 1; part <= 2; part++)
		{
			int hscore = -1;
			while (1)
			{
				// check score and callories of perfect mixture (100 teaspoons)
				if (accumulate(amount.begin(), amount.end(), 0) == total_amount)
				{
					blocked = false;
					int score = 1;
					for (size_t p = 0; p < 5; p++)
					{
						int v = 0;
						for (size_t k = 0; k < input.size(); k++)
							v += amount[k] * input[k][p];

						if (v < 0)
							v = 0;	// zeroing score

						if (p < 4)	// ignoring calories
							score *= v;
						else
						{
							// in part two take into account only 500 callories cookies
							if (part == 2 && v != req_calories)
								blocked = true;
						}
					}

					if (!blocked)
						hscore = max(hscore, score);
				}

				// try different combination of igredients
				size_t i = 0;
				while (1)
				{
					amount[i]++;
					if (amount[i] > total_amount)
					{
						amount[i++] = 0;
						if (i == input.size())
							break;
					}
					else
						break;
				}

				if (i == input.size())
					break;
			}

			result[part - 1] = hscore;
		}

		return result;
	}

	t_vec2int Main::load(const vector<string>& input)
	{
		t_vec2int vinput;
		regex regex("(.*): capacity ([-]?[0-9]*), durability ([-]?[0-9]*), flavor ([-]?[0-9]*), texture ([-]?[0-9])*, calories ([-]?[0-9]*)");
		smatch matches;
		for (const auto& line : input)
		{
			regex_search(line, matches, regex);
			t_vecint v(5);
			for (int i = 0; i < 5; i++)
				v[i] = stoi(matches[i + 2].str());

			vinput.push_back(move(v));
		}

		return vinput;
	}

	AoC::Output Main::both_parts(const vector<string>& input)
	{
		return solve(load(input));
	}
}
