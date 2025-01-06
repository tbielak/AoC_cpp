#include "2024_25.h"

namespace Day25_2024
{
	bool Main::fit(const vector<int>& key, const vector<int>& lock)
	{
		for (int i = 0; i < 5; i++)
			if (key[i] + lock[i] > 5)
				return false;

		return true;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		vector<vector<int>> locks, keys;
		for (size_t j = 0; j < input.size(); j += 8)
		{
			vector<int> v = vector<int>(5, -1);
			for (size_t i = 0; i < 7; i++)
				for (size_t k = 0; k < 5; k++)
					if (input[j + i][k] == '#')
						v[k]++;

			if (input[j] == "#####")
				locks.push_back(v);
			else
				keys.push_back(v);
		}

		int c = 0;
		for (const auto& k : keys)
			for (const auto& l : locks)
				if (fit(k, l))
					c++;

		return c;
	}
}
