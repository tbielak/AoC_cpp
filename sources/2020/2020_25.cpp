#include "2020_25.h"

namespace Day25_2020
{
	int64_t Main::find_loop_size(int64_t key)
	{
		int64_t v = 1;
		int64_t sn = 7;
		int64_t i = 0;
		while (1)
		{
			v = (v * sn) % 20201227;
			i++;
			if (v == key)
				return i;
		}
	}

	int64_t Main::calculate(int64_t key, int64_t loop)
	{
		int64_t v = 1;
		for (int64_t i = 0; i < loop; i++)
			v = (v * key) % 20201227;

		return v;
	}

	AoC::Output Main::part_one(const vector<string>& input)
	{
		int64_t card_public_key = stoi(input[0]);
		int64_t door_public_key = stoi(input[1]);

		return calculate(door_public_key, find_loop_size(card_public_key));
	}
}
