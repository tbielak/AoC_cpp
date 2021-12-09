#include "2021_03.h"

namespace Day03_2021
{
	int part_one(const t_input& x)
	{
		string gamma_bin = x[0];
		string epsilon_bin = x[0];
		for (int i = 0; i < (int)x[0].size(); i++)
		{
			int zeros = (int)count_if(x.begin(), x.end(), [i](const auto& s) { return s[i] == '0'; });
			int ones = (int)x.size() - zeros;
			gamma_bin[i] = char(zeros <= ones) + '0';
			epsilon_bin[i] = char(zeros > ones) + '0';
		}

		int gamma_rate = stoi(gamma_bin, nullptr, 2);
		int epsilon_rate = stoi(epsilon_bin, nullptr, 2);
		return gamma_rate * epsilon_rate;
	}

	int find_rating(const t_input& x, int xor_mask)
	{
		vector<int> consider = vector<int>(x.size(), true);

		while (1)
		{
			for (int i = 0; i < (int)x[0].size(); i++)
			{
				int zeros = 0;
				int ones = 0;
				for (size_t j = 0; j < x.size(); j++)
				{
					if (consider[j])
					{
						if (x[j][i] == '1')
							ones++;
						else
							zeros++;
					}
				}

				char keep = char(((ones >= zeros) ^ xor_mask) + int('0'));
				for (size_t j = 0; j < x.size(); j++)
				{
					if (consider[j])
					{
						if (x[j][i] != keep)
							consider[j] = false;
					}
				}

				if (count_if(consider.begin(), consider.end(), [](const auto& c) { return c; }) == 1)
				{
					for (size_t j = 0; j < x.size(); j++)
						if (consider[j])
							return stoi(x[j], nullptr, 2);
				}
			}
		}
	}

	int part_two(const t_input& x)
	{
		int oxygen_rate = find_rating(x, 0);
		int co2_rate = find_rating(x, 1);
		return oxygen_rate * co2_rate;
	}

	t_output main(const t_input& input)
	{
		auto t0 = chrono::steady_clock::now();
		auto p1 = part_one(input);
		auto p2 = part_two(input);
		auto t1 = chrono::steady_clock::now();

		vector<string> solutions;
		solutions.push_back(to_string(p1));
		solutions.push_back(to_string(p2));
		return make_pair(solutions, chrono::duration<double>((t1 - t0) * 1000).count());
	}
}
