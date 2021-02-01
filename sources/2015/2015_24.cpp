#include "2015_24.h"

namespace Day24_2015
{
	int bit_count(int group, int count)
	{
		int v = 0;
		for (int i = 0; i < count; i++)
		{
			if (group & 1) v++;
			group >>= 1;
		}

		return v;
	}

	int sum_group(const t_vecint& input, int group, int count)
	{
		int v = 0;
		for (int i = count - 1; i >= 0; i--)
		{
			if (group & 1) v += input[i];
			group >>= 1;
		}

		return v;
	}

	uintmax_t QE(const t_vecint& input, int group, int count)
	{
		uintmax_t v = 1;
		for (int i = count - 1; i >= 0; i--)
		{
			if (group & 1) v *= input[i];
			group >>= 1;
		}

		return v;
	}

	vector<uintmax_t> both_parts(const t_vecint& input)
	{
		vector<uintmax_t> result;
		int count = (int)input.size();

		for (int part = 1; part <= 2; part++)
		{
			int total = accumulate(input.begin(), input.end(), 0) / (part + 2);

			t_vecint valid_groups;
			int group_count = 1 << count;
			int min_bc = count;
			for (int group = 1; group < group_count; group++)
			{
				int bc = bit_count(group, count);
				if (bc <= min_bc && sum_group(input, group, count) == total)
				{
					if (bc < min_bc)
					{
						valid_groups.clear();
						min_bc = bc;
					}

					valid_groups.push_back(group);
				}
			}

			uintmax_t minQE = ULLONG_MAX;
			for (const auto& v : valid_groups)
				minQE = min(minQE, QE(input, v, count));

			result.push_back(minQE);
		}

		return result;
	}

	t_output main(const t_input& input)
	{
		t_vecint vinput;
		for (const auto& line : input)
			vinput.push_back(stoi(line));
		
		auto t0 = chrono::steady_clock::now();
		auto px = both_parts(vinput);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(px[0]));
		solutions.push_back(to_string(px[1]));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
