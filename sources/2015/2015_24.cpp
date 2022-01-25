#include "2015_24.h"

namespace Day24_2015
{
	int Main::fast_bit_count(int x)
	{
		// see https://books.google.pl/books?id=iBNKMspIlqEC&pg=PA66&redir_esc=y&hl=pl#v=onepage&q&f=false
		x = x - ((x >> 1) & 0x55555555);
		x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
		x = (x + (x >> 4)) & 0x0f0f0f0f;
		x = x + (x >> 8);
		x = x + (x >> 16);
		return x & 0x3f;
	}

	int Main::sum_group(const t_vecint& input, int group, int count)
	{
		int v = 0;
		for (int i = count - 1; i >= 0; i--)
		{
			if (group & 1) v += input[i];
			group >>= 1;
		}

		return v;
	}

	int64_t Main::QE(const t_vecint& input, int group, int count)
	{
		int64_t v = 1;
		for (int i = count - 1; i >= 0; i--)
		{
			if (group & 1) v *= input[i];
			group >>= 1;
		}

		return v;
	}

	AoC::Output Main::both_parts(const vector<string>& input)
	{
		t_vecint ints;
		for (const auto& line : input)
			ints.push_back(stoi(line));

		vector<int64_t> result;
		int count = (int)ints.size();

		for (int part = 1; part <= 2; part++)
		{
			int total = accumulate(ints.begin(), ints.end(), 0) / (part + 2);

			t_vecint valid_groups;
			int group_count = 1 << count;
			int min_bc = count;
			for (int group = 1; group < group_count; group++)
			{
				int bc = fast_bit_count(group);
				if (bc <= min_bc && sum_group(ints, group, count) == total)
				{
					if (bc < min_bc)
					{
						valid_groups.clear();
						min_bc = bc;
					}

					valid_groups.push_back(group);
				}
			}

			int64_t minQE = LLONG_MAX;
			for (const auto& v : valid_groups)
				minQE = min(minQE, QE(ints, v, count));

			result.push_back(minQE);
		}

		return result;
	}
}
