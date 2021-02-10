#include "2020_24.h"

namespace Day25_2020
{
	uintmax_t find_loop_size(uintmax_t key)
	{
		uintmax_t v = 1;
		uintmax_t sn = 7;
		uintmax_t i = 0;
		while (1)
		{
			v = (v * sn) % 20201227;
			i++;
			if (v == key)
				return i;
		}
	}

	uintmax_t calculate(uintmax_t key, uintmax_t loop)
	{
		uintmax_t v = 1;
		for (uintmax_t i = 0; i < loop; i++)
			v = (v * key) % 20201227;

		return v;
	}

	uintmax_t part_one(uintmax_t card_public_key, uintmax_t door_public_key)
	{
		return calculate(door_public_key, find_loop_size(card_public_key));
	}

	t_output main(const t_input& input)
	{
		uintmax_t card_public_key = stoi(input[0]);
		uintmax_t door_public_key = stoi(input[1]);

		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(card_public_key, door_public_key);
		auto t1 = chrono::steady_clock::now();
		
		vector<string> solutions;
		solutions.push_back(to_string(p1));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
